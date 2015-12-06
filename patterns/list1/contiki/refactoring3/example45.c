switch(flags & SIZE_MASK) {
	  case SIZE_CHAR:
	    uvalue = (unsigned char)va_arg(ap,unsigned int);
	    break;
	  case SIZE_SHORT:
	    uvalue = (unsigned short)va_arg(ap,unsigned int);
	    break;
	  case SIZE_INT:
	    uvalue = va_arg(ap,unsigned int);
	    break;
#ifndef HAVE_LONGLONG
	  case SIZE_LONGLONG:	/* Treat long long the same as long */
#endif
	  case SIZE_LONG:
	    uvalue = va_arg(ap,unsigned long);
	    break;
#ifdef HAVE_LONGLONG
	  case SIZE_LONGLONG:
	    uvalue = va_arg(ap,unsigned long long);
	    break;
#endif
	  }
