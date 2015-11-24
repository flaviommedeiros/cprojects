switch (packet->code) {
			case PW_CODE_ACCESS_REQUEST:
				FR_STATS_INC(auth, total_dup_requests);
				break;

#ifdef WITH_ACCOUNTING
			case PW_CODE_ACCOUNTING_REQUEST:
				FR_STATS_INC(acct, total_dup_requests);
				break;
#endif
#ifdef WITH_COA
			case PW_CODE_COA_REQUEST:
				FR_STATS_INC(coa, total_dup_requests);
				break;

			case PW_CODE_DISCONNECT_REQUEST:
				FR_STATS_INC(dsc, total_dup_requests);
				break;
#endif

			default:
				break;
			}
