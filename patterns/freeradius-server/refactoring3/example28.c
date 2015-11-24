switch (request->proxy_reply->code) {
	case PW_CODE_ACCESS_ACCEPT:
		INC(total_access_accepts);
	proxy_stats:
		INC(total_responses);
		stats_time(&proxy_auth_stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		stats_time(&request->home_server->stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		break;

	case PW_CODE_ACCESS_REJECT:
		INC(total_access_rejects);
		goto proxy_stats;

	case PW_CODE_ACCESS_CHALLENGE:
		INC(total_access_challenges);
		goto proxy_stats;

#ifdef WITH_ACCOUNTING
	case PW_CODE_ACCOUNTING_RESPONSE:
		proxy_acct_stats.total_responses++;
		request->home_server->stats.total_responses++;
		stats_time(&proxy_acct_stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		stats_time(&request->home_server->stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		break;
#endif

#ifdef WITH_COA
	case PW_CODE_COA_ACK:
	case PW_CODE_COA_NAK:
		proxy_coa_stats.total_responses++;
		request->home_server->stats.total_responses++;
		stats_time(&proxy_coa_stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		stats_time(&request->home_server->stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		break;

	case PW_CODE_DISCONNECT_ACK:
	case PW_CODE_DISCONNECT_NAK:
		proxy_dsc_stats.total_responses++;
		request->home_server->stats.total_responses++;
		stats_time(&proxy_dsc_stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		stats_time(&request->home_server->stats,
			   &request->proxy->timestamp,
			   &request->proxy_reply->timestamp);
		break;
#endif

	default:
		proxy_auth_stats.total_unknown_types++;
		request->home_server->stats.total_unknown_types++;
		break;
	}
