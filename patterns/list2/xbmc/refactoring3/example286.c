switch (c)
		{
		case 'd': case 'i':
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
		  break;
		case 'o': case 'u': case 'x': case 'X':
#ifdef HAVE_LONG_LONG
		  if (flags >= 16 || (flags & 4))
		    type = TYPE_ULONGLONGINT;
		  else
#endif
		  if (flags >= 8)
		    type = TYPE_ULONGINT;
		  else if (flags & 2)
		    type = TYPE_UCHAR;
		  else if (flags & 1)
		    type = TYPE_USHORT;
		  else
		    type = TYPE_UINT;
		  break;
		case 'f': case 'F': case 'e': case 'E': case 'g': case 'G':
		case 'a': case 'A':
#ifdef HAVE_LONG_DOUBLE
		  if (flags >= 16 || (flags & 4))
		    type = TYPE_LONGDOUBLE;
		  else
#endif
		  type = TYPE_DOUBLE;
		  break;
		case 'c':
		  if (flags >= 8)
#ifdef HAVE_WINT_T
		    type = TYPE_WIDE_CHAR;
#else
		    goto error;
#endif
		  else
		    type = TYPE_CHAR;
		  break;
#ifdef HAVE_WINT_T
		case 'C':
		  type = TYPE_WIDE_CHAR;
		  c = 'c';
		  break;
#endif
		case 's':
		  if (flags >= 8)
#ifdef HAVE_WCHAR_T
		    type = TYPE_WIDE_STRING;
#else
		    goto error;
#endif
		  else
		    type = TYPE_STRING;
		  break;
#ifdef HAVE_WCHAR_T
		case 'S':
		  type = TYPE_WIDE_STRING;
		  c = 's';
		  break;
#endif
		case 'p':
		  type = TYPE_POINTER;
		  break;
		case 'n':
#ifdef HAVE_LONG_LONG
		  if (flags >= 16 || (flags & 4))
		    type = TYPE_COUNT_LONGLONGINT_POINTER;
		  else
#endif
		  if (flags >= 8)
		    type = TYPE_COUNT_LONGINT_POINTER;
		  else if (flags & 2)
		    type = TYPE_COUNT_SCHAR_POINTER;
		  else if (flags & 1)
		    type = TYPE_COUNT_SHORT_POINTER;
		  else
		    type = TYPE_COUNT_INT_POINTER;
		  break;
		case '%':
		  type = TYPE_NONE;
		  break;
		default:
		  /* Unknown conversion character.  */
		  goto error;
		}
