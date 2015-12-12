switch (var->ind_type)
	{
		case ECPGt_short:
		case ECPGt_unsigned_short:
			if (*(short *) var->ind_value < 0)
				*tobeinserted_p = NULL;
			break;
		case ECPGt_int:
		case ECPGt_unsigned_int:
			if (*(int *) var->ind_value < 0)
				*tobeinserted_p = NULL;
			break;
		case ECPGt_long:
		case ECPGt_unsigned_long:
			if (*(long *) var->ind_value < 0L)
				*tobeinserted_p = NULL;
			break;
#ifdef HAVE_LONG_LONG_INT
		case ECPGt_long_long:
		case ECPGt_unsigned_long_long:
			if (*(long long int *) var->ind_value < (long long) 0)
				*tobeinserted_p = NULL;
			break;
#endif   /* HAVE_LONG_LONG_INT */
		case ECPGt_NO_INDICATOR:
			if (force_indicator == false)
			{
				if (ECPGis_noind_null(var->type, var->value))
					*tobeinserted_p = NULL;
			}
			break;
		default:
			break;
	}
