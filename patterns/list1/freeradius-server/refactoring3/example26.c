switch (request->proxy->code) {
	case PW_CODE_ACCESS_REQUEST:
		proxy_auth_stats.total_requests += request->num_proxied_requests;
		request->home_server->stats.total_requests += request->num_proxied_requests;
		break;

#ifdef WITH_ACCOUNTING
	case PW_CODE_ACCOUNTING_REQUEST:
		proxy_acct_stats.total_requests += request->num_proxied_requests;
		request->home_server->stats.total_requests += request->num_proxied_requests;
		break;
#endif

#ifdef WITH_COA
	case PW_CODE_COA_REQUEST:
		proxy_coa_stats.total_requests += request->num_proxied_requests;
		request->home_server->stats.total_requests += request->num_proxied_requests;
		break;

	case PW_CODE_DISCONNECT_REQUEST:
		proxy_dsc_stats.total_requests += request->num_proxied_requests;
		request->home_server->stats.total_requests += request->num_proxied_requests;
		break;
#endif

	default:
		break;
	}
