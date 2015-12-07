#ifdef	G_HAVE_GINT64
if (extra_long)
		    (void) va_arg (args, gint64);
		  else
#endif	/* G_HAVE_GINT64 */
		    {
		      if (long_int)
			(void) va_arg (args, long);
		      else
			(void) va_arg (args, int);
		    }
