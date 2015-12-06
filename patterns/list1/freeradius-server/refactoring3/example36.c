switch (request->proxy->code) {
	case PW_CODE_ACCESS_REQUEST:
		proxy_auth_stats.last_packet = packet->timestamp.tv_sec;

		if (request->proxy_reply->code == PW_CODE_ACCESS_ACCEPT) {
			request->proxy_listener->stats.total_access_accepts++;

		} else if (request->proxy_reply->code == PW_CODE_ACCESS_REJECT) {
			request->proxy_listener->stats.total_access_rejects++;

		} else if (request->proxy_reply->code == PW_CODE_ACCESS_CHALLENGE) {
			request->proxy_listener->stats.total_access_challenges++;
		}
		break;

#ifdef WITH_ACCOUNTING
	case PW_CODE_ACCOUNTING_REQUEST:
		proxy_acct_stats.last_packet = packet->timestamp.tv_sec;

		request->proxy_listener->stats.total_responses++;
		proxy_acct_stats.last_packet = packet->timestamp.tv_sec;
		break;

#endif

#ifdef WITH_COA
	case PW_CODE_COA_REQUEST:
		request->proxy_listener->stats.total_responses++;
		proxy_coa_stats.last_packet = packet->timestamp.tv_sec;
		break;

	case PW_CODE_DISCONNECT_REQUEST:
		request->proxy_listener->stats.total_responses++;
		proxy_dsc_stats.last_packet = packet->timestamp.tv_sec;
		break;

#endif
	default:
		break;
	}
