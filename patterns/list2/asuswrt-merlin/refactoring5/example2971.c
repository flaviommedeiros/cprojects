# ifdef HAVE_LONG_LONG
if (type == TYPE_LONGLONGINT || type == TYPE_ULONGLONGINT)
			tmp_length =
			  (unsigned int) (sizeof (unsigned long long) * CHAR_BIT
					  * 0.333334 /* binary -> octal */
					 )
			  + 1 /* turn floor into ceil */
			  + 1; /* account for leading sign */
		      else
# endif
		      if (type == TYPE_LONGINT || type == TYPE_ULONGINT)
			tmp_length =
			  (unsigned int) (sizeof (unsigned long) * CHAR_BIT
					  * 0.333334 /* binary -> octal */
					 )
			  + 1 /* turn floor into ceil */
			  + 1; /* account for leading sign */
		      else
			tmp_length =
			  (unsigned int) (sizeof (unsigned int) * CHAR_BIT
					  * 0.333334 /* binary -> octal */
					 )
			  + 1 /* turn floor into ceil */
			  + 1;
