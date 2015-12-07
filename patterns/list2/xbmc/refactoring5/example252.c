#ifdef USE_IN_LIBIO
if (_IO_fwide (fs->stream, 0) > 0)
		    putwc_unlocked (L' ', fs->stream);
		  else
#endif
		    putc_unlocked (' ', fs->stream);
