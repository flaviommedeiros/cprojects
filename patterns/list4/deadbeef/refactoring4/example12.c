#if defined _LIBC || HAVE_ICONV
if (encoding != NULL)
# else
  if (convert)
# endif
    {
      /* We are supposed to do a conversion.  */
# ifndef IN_LIBGLOCALE
      const char *encoding = get_output_charset (domainbinding);
# endif
      size_t nconversions;
      struct converted_domain *convd;
      size_t i;

      /* Protect against reallocation of the table.  */
      gl_rwlock_rdlock (domain->conversions_lock);

      /* Search whether a table with converted translations for this
	 encoding has already been allocated.  */
      nconversions = domain->nconversions;
      convd = NULL;

      for (i = nconversions; i > 0; )
	{
	  i--;
	  if (strcmp (domain->conversions[i].encoding, encoding) == 0)
	    {
	      convd = &domain->conversions[i];
	      break;
	    }
	}

      gl_rwlock_unlock (domain->conversions_lock);

      if (convd == NULL)
	{
	  /* We have to allocate a new conversions table.  */
	  gl_rwlock_wrlock (domain->conversions_lock);
	  nconversions = domain->nconversions;

	  /* Maybe in the meantime somebody added the translation.
	     Recheck.  */
	  for (i = nconversions; i > 0; )
	    {
	      i--;
	      if (strcmp (domain->conversions[i].encoding, encoding) == 0)
		{
		  convd = &domain->conversions[i];
		  goto found_convd;
		}
	    }

	  {
	    /* Allocate a table for the converted translations for this
	       encoding.  */
	    struct converted_domain *new_conversions =
	      (struct converted_domain *)
	      (domain->conversions != NULL
	       ? realloc (domain->conversions,
			  (nconversions + 1) * sizeof (struct converted_domain))
	       : malloc ((nconversions + 1) * sizeof (struct converted_domain)));

	    if (__builtin_expect (new_conversions == NULL, 0))
	      {
		/* Nothing we can do, no more memory.  We cannot use the
		   translation because it might be encoded incorrectly.  */
	      unlock_fail:
		gl_rwlock_unlock (domain->conversions_lock);
		return (char *) -1;
	      }

	    domain->conversions = new_conversions;

	    /* Copy the 'encoding' string to permanent storage.  */
	    encoding = strdup (encoding);
	    if (__builtin_expect (encoding == NULL, 0))
	      /* Nothing we can do, no more memory.  We cannot use the
		 translation because it might be encoded incorrectly.  */
	      goto unlock_fail;

	    convd = &new_conversions[nconversions];
	    convd->encoding = encoding;

	    /* Find out about the character set the file is encoded with.
	       This can be found (in textual form) in the entry "".  If this
	       entry does not exist or if this does not contain the 'charset='
	       information, we will assume the charset matches the one the
	       current locale and we don't have to perform any conversion.  */
# ifdef _LIBC
	    convd->conv = (__gconv_t) -1;
# else
#  if HAVE_ICONV
	    convd->conv = (iconv_t) -1;
#  endif
# endif
	    {
	      char *nullentry;
	      size_t nullentrylen;

	      /* Get the header entry.  This is a recursion, but it doesn't
		 reallocate domain->conversions because we pass
		 encoding = NULL or convert = 0, respectively.  */
	      nullentry =
# ifdef IN_LIBGLOCALE
		_nl_find_msg (domain_file, domainbinding, NULL, "",
			      &nullentrylen);
# else
		_nl_find_msg (domain_file, domainbinding, "", 0, &nullentrylen);
# endif

	      if (nullentry != NULL)
		{
		  const char *charsetstr;

		  charsetstr = strstr (nullentry, "charset=");
		  if (charsetstr != NULL)
		    {
		      size_t len;
		      char *charset;
		      const char *outcharset;

		      charsetstr += strlen ("charset=");
		      len = strcspn (charsetstr, " \t\n");

		      charset = (char *) alloca (len + 1);
# if defined _LIBC || HAVE_MEMPCPY
		      *((char *) mempcpy (charset, charsetstr, len)) = '\0';
# else
		      memcpy (charset, charsetstr, len);
		      charset[len] = '\0';
# endif

		      outcharset = encoding;

# ifdef _LIBC
		      /* We always want to use transliteration.  */
		      outcharset = norm_add_slashes (outcharset, "TRANSLIT");
		      charset = norm_add_slashes (charset, "");
		      int r = __gconv_open (outcharset, charset, &convd->conv,
					    GCONV_AVOID_NOCONV);
		      if (__builtin_expect (r != __GCONV_OK, 0))
			{
			  /* If the output encoding is the same there is
			     nothing to do.  Otherwise do not use the
			     translation at all.  */
			  if (__builtin_expect (r != __GCONV_NULCONV, 1))
			    {
			      gl_rwlock_unlock (domain->conversions_lock);
			      free ((char *) encoding);
			      return NULL;
			    }

			  convd->conv = (__gconv_t) -1;
			}
# else
#  if HAVE_ICONV
		      /* When using GNU libc >= 2.2 or GNU libiconv >= 1.5,
			 we want to use transliteration.  */
#   if (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 2) || __GLIBC__ > 2 \
       || _LIBICONV_VERSION >= 0x0105
		      if (strchr (outcharset, '/') == NULL)
			{
			  char *tmp;

			  len = strlen (outcharset);
			  tmp = (char *) alloca (len + 10 + 1);
			  memcpy (tmp, outcharset, len);
			  memcpy (tmp + len, "//TRANSLIT", 10 + 1);
			  outcharset = tmp;

			  convd->conv = iconv_open (outcharset, charset);

			  freea (outcharset);
			}
		      else
#   endif
			convd->conv = iconv_open (outcharset, charset);
#  endif
# endif

		      freea (charset);
		    }
		}
	    }
	    convd->conv_tab = NULL;
	    /* Here domain->conversions is still == new_conversions.  */
	    domain->nconversions++;
	  }

	found_convd:
	  gl_rwlock_unlock (domain->conversions_lock);
	}

      if (
# ifdef _LIBC
	  convd->conv != (__gconv_t) -1
# else
#  if HAVE_ICONV
	  convd->conv != (iconv_t) -1
#  endif
# endif
	  )
	{
	  /* We are supposed to do a conversion.  First allocate an
	     appropriate table with the same structure as the table
	     of translations in the file, where we can put the pointers
	     to the converted strings in.
	     There is a slight complication with plural entries.  They
	     are represented by consecutive NUL terminated strings.  We
	     handle this case by converting RESULTLEN bytes, including
	     NULs.  */

	  /* This lock primarily protects the memory management variables
	     freemem, freemem_size.  It also protects write accesses to
	     convd->conv_tab.  It's not worth using a separate lock (such
	     as domain->conversions_lock) for this purpose, because when
	     modifying convd->conv_tab, we also need to lock freemem,
	     freemem_size for most of the time.  */
	  __libc_lock_define_initialized (static, lock)

	  if (__builtin_expect (convd->conv_tab == NULL, 0))
	    {
	      __libc_lock_lock (lock);
	      if (convd->conv_tab == NULL)
		{
		  convd->conv_tab =
		    (char **) calloc (nstrings + domain->n_sysdep_strings,
				      sizeof (char *));
		  if (convd->conv_tab != NULL)
		    goto not_translated_yet;
		  /* Mark that we didn't succeed allocating a table.  */
		  convd->conv_tab = (char **) -1;
		}
	      __libc_lock_unlock (lock);
	    }

	  if (__builtin_expect (convd->conv_tab == (char **) -1, 0))
	    /* Nothing we can do, no more memory.  We cannot use the
	       translation because it might be encoded incorrectly.  */
	    return (char *) -1;

	  if (convd->conv_tab[act] == NULL)
	    {
	      /* We haven't used this string so far, so it is not
		 translated yet.  Do this now.  */
	      /* We use a bit more efficient memory handling.
		 We allocate always larger blocks which get used over
		 time.  This is faster than many small allocations.   */
# define INITIAL_BLOCK_SIZE	4080
	      static unsigned char *freemem;
	      static size_t freemem_size;

	      const unsigned char *inbuf;
	      unsigned char *outbuf;
	      int malloc_count;
# ifndef _LIBC
	      transmem_block_t *transmem_list;
# endif

	      __libc_lock_lock (lock);
	    not_translated_yet:

	      inbuf = (const unsigned char *) result;
	      outbuf = freemem + sizeof (size_t);
# ifndef _LIBC
	      transmem_list = NULL;
# endif

	      malloc_count = 0;
	      while (1)
		{
		  transmem_block_t *newmem;
# ifdef _LIBC
		  size_t non_reversible;
		  int res;

		  if (freemem_size < sizeof (size_t))
		    goto resize_freemem;

		  res = __gconv (convd->conv,
				 &inbuf, inbuf + resultlen,
				 &outbuf,
				 outbuf + freemem_size - sizeof (size_t),
				 &non_reversible);

		  if (res == __GCONV_OK || res == __GCONV_EMPTY_INPUT)
		    break;

		  if (res != __GCONV_FULL_OUTPUT)
		    {
		      /* We should not use the translation at all, it
			 is incorrectly encoded.  */
		      __libc_lock_unlock (lock);
		      return NULL;
		    }

		  inbuf = (const unsigned char *) result;
# else
#  if HAVE_ICONV
		  const char *inptr = (const char *) inbuf;
		  size_t inleft = resultlen;
		  char *outptr = (char *) outbuf;
		  size_t outleft;

		  if (freemem_size < sizeof (size_t))
		    goto resize_freemem;

		  outleft = freemem_size - sizeof (size_t);
		  if (iconv (convd->conv,
			     (ICONV_CONST char **) &inptr, &inleft,
			     &outptr, &outleft)
		      != (size_t) (-1))
		    {
		      outbuf = (unsigned char *) outptr;
		      break;
		    }
		  if (errno != E2BIG)
		    {
		      __libc_lock_unlock (lock);
		      return NULL;
		    }
#  endif
# endif

		resize_freemem:
		  /* We must allocate a new buffer or resize the old one.  */
		  if (malloc_count > 0)
		    {
		      ++malloc_count;
		      freemem_size = malloc_count * INITIAL_BLOCK_SIZE;
		      newmem = (transmem_block_t *) realloc (transmem_list,
							     freemem_size);
# ifdef _LIBC
		      if (newmem != NULL)
			transmem_list = transmem_list->next;
		      else
			{
			  struct transmem_list *old = transmem_list;

			  transmem_list = transmem_list->next;
			  free (old);
			}
# endif
		    }
		  else
		    {
		      malloc_count = 1;
		      freemem_size = INITIAL_BLOCK_SIZE;
		      newmem = (transmem_block_t *) malloc (freemem_size);
		    }
		  if (__builtin_expect (newmem == NULL, 0))
		    {
		      freemem = NULL;
		      freemem_size = 0;
		      __libc_lock_unlock (lock);
		      return (char *) -1;
		    }

# ifdef _LIBC
		  /* Add the block to the list of blocks we have to free
		     at some point.  */
		  newmem->next = transmem_list;
		  transmem_list = newmem;

		  freemem = (unsigned char *) newmem->data;
		  freemem_size -= offsetof (struct transmem_list, data);
# else
		  transmem_list = newmem;
		  freemem = newmem;
# endif

		  outbuf = freemem + sizeof (size_t);
		}

	      /* We have now in our buffer a converted string.  Put this
		 into the table of conversions.  */
	      *(size_t *) freemem = outbuf - freemem - sizeof (size_t);
	      convd->conv_tab[act] = (char *) freemem;
	      /* Shrink freemem, but keep it aligned.  */
	      freemem_size -= outbuf - freemem;
	      freemem = outbuf;
	      freemem += freemem_size & (alignof (size_t) - 1);
	      freemem_size = freemem_size & ~ (alignof (size_t) - 1);

	      __libc_lock_unlock (lock);
	    }

	  /* Now convd->conv_tab[act] contains the translation of all
	     the plural variants.  */
	  result = convd->conv_tab[act] + sizeof (size_t);
	  resultlen = *(size_t *) convd->conv_tab[act];
	}
    }
