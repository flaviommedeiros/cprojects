#ifdef HAVE_LONG_DOUBLE
if (flags >= 16 || (flags & 4))
		    type = TYPE_LONGDOUBLE;
		  else
#endif
		  type = TYPE_DOUBLE;
