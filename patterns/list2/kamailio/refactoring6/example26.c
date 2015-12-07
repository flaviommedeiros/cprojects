if (fnmatch( check_val.s.s, avp_val.s.s,
			#ifdef FNM_CASEFOLD
			(val->ops&AVPOPS_FLAG_CI)?FNM_CASEFOLD:
			#endif
			0 )==0)
			{
				avp_val.s.s[avp_val.s.len] = backup;
				return 1;
			}
