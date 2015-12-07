#ifdef USE_IN_LIBIO
if (_IO_fwide (stream, 0) > 0)
		__fwprintf (stream, L": %s",
			    __strerror_r (errnum, buf, sizeof (buf)));
	      else
#endif
		{
		  char const *s = NULL;
		  putc_unlocked (':', stream);
		  putc_unlocked (' ', stream);
#if _LIBC || (HAVE_DECL_STRERROR_R && STRERROR_R_CHAR_P)
		  s = __strerror_r (errnum, buf, sizeof buf);
#elif HAVE_DECL_STRERROR_R
		  if (__strerror_r (errnum, buf, sizeof buf) == 0)
		    s = buf;
#endif
#if !_LIBC
		  if (! s && ! (s = strerror (errnum)))
		    s = dgettext (state->root_argp->argp_domain,
				  "Unknown system error");
#endif
		  fputs (s, stream);
		}
