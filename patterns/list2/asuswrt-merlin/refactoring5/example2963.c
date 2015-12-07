#ifdef HAVE_LONG_LONG
if (flags >= 16 || (flags & 4))
		    type = TYPE_LONGLONGINT;
		  else
#endif
		  if (flags >= 8)
		    type = TYPE_LONGINT;
		  else if (flags & 2)
		    type = TYPE_SCHAR;
		  else if (flags & 1)
		    type = TYPE_SHORT;
		  else
		    type = TYPE_INT;
