switch (request->listener->type) {
#ifdef WITH_STATS
	case RAD_LISTEN_NONE:
#endif
	case RAD_LISTEN_AUTH:
		dval = fr_dict_enum_by_name(NULL, fr_dict_attr_by_num(NULL, 0, PW_AUTZ_TYPE), "Status-Server");
		if (dval) {
			rcode = process_authorize(dval->value, request);
		} else {
			rcode = RLM_MODULE_OK;
		}

		switch (rcode) {
		case RLM_MODULE_OK:
		case RLM_MODULE_UPDATED:
			request->reply->code = PW_CODE_ACCESS_ACCEPT;
			break;

		case RLM_MODULE_FAIL:
		case RLM_MODULE_HANDLED:
			request->reply->code = 0; /* don't reply */
			break;

		default:
		case RLM_MODULE_REJECT:
			request->reply->code = PW_CODE_ACCESS_REJECT;
			break;
		}
		break;

#ifdef WITH_ACCOUNTING
	case RAD_LISTEN_ACCT:
		dval = fr_dict_enum_by_name(NULL, fr_dict_attr_by_num(NULL, 0, PW_ACCT_TYPE), "Status-Server");
		if (dval) {
			rcode = process_accounting(dval->value, request);
		} else {
			rcode = RLM_MODULE_OK;
		}

		switch (rcode) {
		case RLM_MODULE_OK:
		case RLM_MODULE_UPDATED:
			request->reply->code = PW_CODE_ACCOUNTING_RESPONSE;
			break;

		default:
			request->reply->code = 0; /* don't reply */
			break;
		}
		break;
#endif

#ifdef WITH_COA
		/*
		 *	This is a vendor extension.  Suggested by Glen
		 *	Zorn in IETF 72, and rejected by the rest of
		 *	the WG.  We like it, so it goes in here.
		 */
	case RAD_LISTEN_COA:
		dval = fr_dict_enum_by_name(NULL, fr_dict_attr_by_num(NULL, 0, PW_RECV_COA_TYPE), "Status-Server");
		if (dval) {
			rcode = process_recv_coa(dval->value, request);
		} else {
			rcode = RLM_MODULE_OK;
		}

		switch (rcode) {
		case RLM_MODULE_OK:
		case RLM_MODULE_UPDATED:
			request->reply->code = PW_CODE_COA_ACK;
			break;

		default:
			request->reply->code = 0; /* don't reply */
			break;
		}
		break;
#endif

	default:
		return 0;
	}
