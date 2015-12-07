switch (type)
		      {
		      case TYPE_SCHAR:
			{
			  int arg = a.arg[dp->arg_index].a.a_schar;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_UCHAR:
			{
			  unsigned int arg = a.arg[dp->arg_index].a.a_uchar;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_SHORT:
			{
			  int arg = a.arg[dp->arg_index].a.a_short;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_USHORT:
			{
			  unsigned int arg = a.arg[dp->arg_index].a.a_ushort;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_INT:
			{
			  int arg = a.arg[dp->arg_index].a.a_int;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_UINT:
			{
			  unsigned int arg = a.arg[dp->arg_index].a.a_uint;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_LONGINT:
			{
			  long int arg = a.arg[dp->arg_index].a.a_longint;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_ULONGINT:
			{
			  unsigned long int arg = a.arg[dp->arg_index].a.a_ulongint;
			  SNPRINTF_BUF (arg);
			}
			break;
#ifdef HAVE_LONG_LONG
		      case TYPE_LONGLONGINT:
			{
			  long long int arg = a.arg[dp->arg_index].a.a_longlongint;
			  SNPRINTF_BUF (arg);
			}
			break;
		      case TYPE_ULONGLONGINT:
			{
			  unsigned long long int arg = a.arg[dp->arg_index].a.a_ulonglongint;
			  SNPRINTF_BUF (arg);
			}
			break;
#endif
		      case TYPE_DOUBLE:
			{
			  double arg = a.arg[dp->arg_index].a.a_double;
			  SNPRINTF_BUF (arg);
			}
			break;
#ifdef HAVE_LONG_DOUBLE
		      case TYPE_LONGDOUBLE:
			{
			  long double arg = a.arg[dp->arg_index].a.a_longdouble;
			  SNPRINTF_BUF (arg);
			}
			break;
#endif
		      case TYPE_CHAR:
			{
			  int arg = a.arg[dp->arg_index].a.a_char;
			  SNPRINTF_BUF (arg);
			}
			break;
#ifdef HAVE_WINT_T
		      case TYPE_WIDE_CHAR:
			{
			  wint_t arg = a.arg[dp->arg_index].a.a_wide_char;
			  SNPRINTF_BUF (arg);
			}
			break;
#endif
		      case TYPE_STRING:
			{
			  const char *arg = a.arg[dp->arg_index].a.a_string;
			  SNPRINTF_BUF (arg);
			}
			break;
#ifdef HAVE_WCHAR_T
		      case TYPE_WIDE_STRING:
			{
			  const wchar_t *arg = a.arg[dp->arg_index].a.a_wide_string;
			  SNPRINTF_BUF (arg);
			}
			break;
#endif
		      case TYPE_POINTER:
			{
			  void *arg = a.arg[dp->arg_index].a.a_pointer;
			  SNPRINTF_BUF (arg);
			}
			break;
		      default:
			abort ();
		      }
