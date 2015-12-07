#ifdef USE_IN_LIBIO
if (_IO_fwide (stream, 0) > 0)
	    putwc_unlocked (L'\n', stream);
	  else
#endif
	    putc_unlocked ('\n', stream);
