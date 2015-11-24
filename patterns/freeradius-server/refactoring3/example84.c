switch (request->packet->code) {
		default:
			REDEBUG2("Cannot replicate unknown packet code %d", request->packet->code);
			rcode = RLM_MODULE_FAIL;
			goto done;

		case PW_CODE_ACCESS_REQUEST:
			pool = realm->auth_pool;
			break;

#ifdef WITH_ACCOUNTING

		case PW_CODE_ACCOUNTING_REQUEST:
			pool = realm->acct_pool;
			break;
#endif

#ifdef WITH_COA
		case PW_CODE_COA_REQUEST:
		case PW_CODE_DISCONNECT_REQUEST:
			pool = realm->coa_pool;
			break;
#endif
		}
