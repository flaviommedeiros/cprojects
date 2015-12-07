#ifdef HAVE_LONG_DOUBLE
if (extra_long)
		    (void) va_arg (args, long double);
		  else
#endif	/* HAVE_LONG_DOUBLE */
		    (void) va_arg (args, double);
