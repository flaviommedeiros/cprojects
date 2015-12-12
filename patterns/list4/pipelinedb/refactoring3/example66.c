switch (vartype)
	{
		case ECPGt_short:
			*target = *(const short *) var;
			break;
		case ECPGt_int:
			*target = *(const int *) var;
			break;
		case ECPGt_long:
			*target = *(const long *) var;
			break;
		case ECPGt_unsigned_short:
			*target = *(const unsigned short *) var;
			break;
		case ECPGt_unsigned_int:
			*target = *(const unsigned int *) var;
			break;
		case ECPGt_unsigned_long:
			*target = *(const unsigned long *) var;
			break;
#ifdef HAVE_LONG_LONG_INT
		case ECPGt_long_long:
			*target = *(const long long int *) var;
			break;
		case ECPGt_unsigned_long_long:
			*target = *(const unsigned long long int *) var;
			break;
#endif   /* HAVE_LONG_LONG_INT */
		case ECPGt_float:
			*target = *(const float *) var;
			break;
		case ECPGt_double:
			*target = *(const double *) var;
			break;
		default:
			ecpg_raise(lineno, ECPG_VAR_NOT_NUMERIC, ECPG_SQLSTATE_RESTRICTED_DATA_TYPE_ATTRIBUTE_VIOLATION, NULL);
			return (false);
	}
