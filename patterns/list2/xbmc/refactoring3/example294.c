switch (type)
		  {
#ifdef HAVE_LONG_LONG
		  case TYPE_LONGLONGINT:
		  case TYPE_ULONGLONGINT:
		    *p++ = 'l';
		    /*FALLTHROUGH*/
#endif
		  case TYPE_LONGINT:
		  case TYPE_ULONGINT:
#ifdef HAVE_WINT_T
		  case TYPE_WIDE_CHAR:
#endif
#ifdef HAVE_WCHAR_T
		  case TYPE_WIDE_STRING:
#endif
		    *p++ = 'l';
		    break;
#ifdef HAVE_LONG_DOUBLE
		  case TYPE_LONGDOUBLE:
		    *p++ = 'L';
		    break;
#endif
		  default:
		    break;
		  }
