#ifdef USE_IN_LIBIO
if (_IO_fwide (stream, 0) > 0)
	    __fwprintf (stream, L"%s",
			state ? state->name : __argp_short_program_name ());
	  else
#endif
	    fputs_unlocked (state
			    ? state->name : __argp_short_program_name (),
			    stream);
