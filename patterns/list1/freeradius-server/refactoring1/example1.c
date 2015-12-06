if (packet->code == PW_CODE_ACCESS_REQUEST) {
		request->client->auth.last_packet = request->packet->timestamp.tv_sec;
		radius_auth_stats.last_packet = request->packet->timestamp.tv_sec;
#ifdef WITH_ACCOUNTING
	} else if (packet->code == PW_CODE_ACCOUNTING_REQUEST) {
		request->client->acct.last_packet = request->packet->timestamp.tv_sec;
		radius_acct_stats.last_packet = request->packet->timestamp.tv_sec;
#endif
	}
#endif
