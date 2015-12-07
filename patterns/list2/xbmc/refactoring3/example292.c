switch (a.arg[dp->arg_index].type)
		  {
		  case TYPE_COUNT_SCHAR_POINTER:
		    *a.arg[dp->arg_index].a.a_count_schar_pointer = length;
		    break;
		  case TYPE_COUNT_SHORT_POINTER:
		    *a.arg[dp->arg_index].a.a_count_short_pointer = length;
		    break;
		  case TYPE_COUNT_INT_POINTER:
		    *a.arg[dp->arg_index].a.a_count_int_pointer = length;
		    break;
		  case TYPE_COUNT_LONGINT_POINTER:
		    *a.arg[dp->arg_index].a.a_count_longint_pointer = length;
		    break;
#ifdef HAVE_LONG_LONG
		  case TYPE_COUNT_LONGLONGINT_POINTER:
		    *a.arg[dp->arg_index].a.a_count_longlongint_pointer = length;
		    break;
#endif
		  default:
		    abort ();
		  }
