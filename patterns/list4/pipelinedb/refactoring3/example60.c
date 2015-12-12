switch (ind_type)
	{
		case ECPGt_short:
		case ECPGt_unsigned_short:
			*((short *) (ind + ind_offset * act_tuple)) = value_for_indicator;
			break;
		case ECPGt_int:
		case ECPGt_unsigned_int:
			*((int *) (ind + ind_offset * act_tuple)) = value_for_indicator;
			break;
		case ECPGt_long:
		case ECPGt_unsigned_long:
			*((long *) (ind + ind_offset * act_tuple)) = value_for_indicator;
			break;
#ifdef HAVE_LONG_LONG_INT
		case ECPGt_long_long:
		case ECPGt_unsigned_long_long:
			*((long long int *) (ind + ind_offset * act_tuple)) = value_for_indicator;
			break;
#endif   /* HAVE_LONG_LONG_INT */
		case ECPGt_NO_INDICATOR:
			if (value_for_indicator == -1)
			{
				if (force_indicator == false)
				{
					/*
					 * Informix has an additional way to specify NULLs note
					 * that this uses special values to denote NULL
					 */
					ECPGset_noind_null(type, var + offset * act_tuple);
				}
				else
				{
					ecpg_raise(lineno, ECPG_MISSING_INDICATOR,
							 ECPG_SQLSTATE_NULL_VALUE_NO_INDICATOR_PARAMETER,
							   NULL);
					return (false);
				}
			}
			break;
		default:
			ecpg_raise(lineno, ECPG_UNSUPPORTED,
					   ECPG_SQLSTATE_ECPG_INTERNAL_ERROR,
					   ecpg_type_name(ind_type));
			return (false);
			break;
	}
