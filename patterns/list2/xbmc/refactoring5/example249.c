#ifdef USE_IN_LIBIO
if (_IO_fwide (stream, 0) > 0)
		{
		  char *buf;

		  if (__asprintf (&buf, fmt, ap) < 0)
		    buf = NULL;

		  __fwprintf (stream, L": %s", buf);

		  free (buf);
		}
	      else
#endif
		{
		  putc_unlocked (':', stream);
		  putc_unlocked (' ', stream);

		  vfprintf (stream, fmt, ap);
		}
