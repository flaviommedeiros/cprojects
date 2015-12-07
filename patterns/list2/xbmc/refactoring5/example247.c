#ifdef USE_IN_LIBIO
if (_IO_fwide (stream, 0) > 0)
	    {
	      char *buf;

	      if (__asprintf (&buf, fmt, ap) < 0)
		buf = NULL;

	      __fwprintf (stream, L"%s: %s\n",
			  state ? state->name : __argp_short_program_name (),
			  buf);

	      free (buf);
	    }
	  else
#endif
	    {
	      fputs_unlocked (state
			      ? state->name : __argp_short_program_name (),
			      stream);
	      putc_unlocked (':', stream);
	      putc_unlocked (' ', stream);

	      vfprintf (stream, fmt, ap);

	      putc_unlocked ('\n', stream);
	    }
