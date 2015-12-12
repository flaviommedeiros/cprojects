switch (vartype)
	{
		case ECPGt_short:
			*(short *) var = (short) value;
			break;
		case ECPGt_int:
			*(int *) var = (int) value;
			break;
		case ECPGt_long:
			*(long *) var = (long) value;
			break;
		case ECPGt_unsigned_short:
			*(unsigned short *) var = (unsigned short) value;
			break;
		case ECPGt_unsigned_int:
			*(unsigned int *) var = (unsigned int) value;
			break;
		case ECPGt_unsigned_long:
			*(unsigned long *) var = (unsigned long) value;
			break;
#ifdef HAVE_LONG_LONG_INT
		case ECPGt_long_long:
			*(long long int *) var = (long long int) value;
			break;
		case ECPGt_unsigned_long_long:
			*(unsigned long long int *) var = (unsigned long long int) value;
			break;
#endif   /* HAVE_LONG_LONG_INT */
		case ECPGt_float:
			*(float *) var = (float) value;
			break;
		case ECPGt_double:
			*(double *) var = (double) value;
			break;
		default:
			ecpg_raise(lineno, ECPG_VAR_NOT_NUMERIC, ECPG_SQLSTATE_RESTRICTED_DATA_TYPE_ATTRIBUTE_VIOLATION, NULL);
			return (false);
	}
