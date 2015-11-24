switch (request->reply->code) {
	case PW_CODE_ACCESS_ACCEPT:
		INC_AUTH(total_access_accepts);

		auth_stats:
		INC_AUTH(total_responses);

		/*
		 *	FIXME: Do the time calculations once...
		 */
		stats_time(&radius_auth_stats,
			   &request->packet->timestamp,
			   &request->reply->timestamp);
		stats_time(&request->client->auth,
			   &request->packet->timestamp,
			   &request->reply->timestamp);
		stats_time(&request->listener->stats,
			   &request->packet->timestamp,
			   &request->reply->timestamp);
		break;

	case PW_CODE_ACCESS_REJECT:
		INC_AUTH(total_access_rejects);
		goto auth_stats;

	case PW_CODE_ACCESS_CHALLENGE:
		INC_AUTH(total_access_challenges);
		goto auth_stats;

#ifdef WITH_ACCOUNTING
	case PW_CODE_ACCOUNTING_RESPONSE:
		INC_ACCT(total_responses);
		stats_time(&radius_acct_stats,
			   &request->packet->timestamp,
			   &request->reply->timestamp);
		stats_time(&request->client->acct,
			   &request->packet->timestamp,
			   &request->reply->timestamp);
		break;
#endif

#ifdef WITH_COA
	case PW_CODE_COA_ACK:
		INC_COA(total_access_accepts);
	  coa_stats:
		INC_COA(total_responses);
		stats_time(&request->client->coa,
			   &request->packet->timestamp,
			   &request->reply->timestamp);
		break;

	case PW_CODE_COA_NAK:
		INC_COA(total_access_rejects);
		goto coa_stats;

	case PW_CODE_DISCONNECT_ACK:
		INC_DSC(total_access_accepts);
	  dsc_stats:
		INC_DSC(total_responses);
		stats_time(&request->client->dsc,
			   &request->packet->timestamp,
			   &request->reply->timestamp);
		break;

	case PW_CODE_DISCONNECT_NAK:
		INC_DSC(total_access_rejects);
		goto dsc_stats;
#endif

		/*
		 *	No response, it must have been a bad
		 *	authenticator.
		 */
	case 0:
		if (request->packet->code == PW_CODE_ACCESS_REQUEST) {
			if (request->reply->offset == -2) {
				INC_AUTH(total_bad_authenticators);
			} else {
				INC_AUTH(total_packets_dropped);
			}
		} else if (request->packet->code == PW_CODE_ACCOUNTING_REQUEST) {
			if (request->reply->offset == -2) {
				INC_ACCT(total_bad_authenticators);
			} else {
				INC_ACCT(total_packets_dropped);
			}
		}
		break;

	default:
		break;
	}
