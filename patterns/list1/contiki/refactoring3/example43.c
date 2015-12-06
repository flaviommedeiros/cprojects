switch(flags & SIZE_MASK) {
	  case SIZE_CHAR:
	    value = (signed char)va_arg(ap, int);
	    break;
	  case SIZE_SHORT:
	    value = (short)va_arg(ap, int);
	    break;
	  case SIZE_INT:
	    value = va_arg(ap, int);
	    break;
#ifndef HAVE_LONGLONG
	  case SIZE_LONGLONG:	/* Treat long long the same as long */
#endif
	  case SIZE_LONG:
	    value = va_arg(ap, long);
	    break;
#ifdef HAVE_LONGLONG
	  case SIZE_LONGLONG:
	    value = va_arg(ap, long long);
	    break;
#endif
	  }
