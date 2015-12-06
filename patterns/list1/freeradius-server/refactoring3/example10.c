switch (packet->code) {
	case PW_CODE_ACCESS_REQUEST:
		if (listener->type != RAD_LISTEN_AUTH) goto bad_packet;
		FR_STATS_INC(auth, total_requests);
		fun = rad_authenticate;
		break;

#  ifdef WITH_ACCOUNTING
	case PW_CODE_ACCOUNTING_REQUEST:
		if (listener->type != RAD_LISTEN_ACCT) goto bad_packet;
		FR_STATS_INC(acct, total_requests);
		fun = rad_accounting;
		break;
#  endif

	case PW_CODE_STATUS_SERVER:
		if (!main_config.status_server) {
			FR_STATS_INC(auth, total_unknown_types);
			WARN("Ignoring Status-Server request due to security configuration");
			rad_free(&sock->packet);
			return 0;
		}
		fun = rad_status_server;
		break;

	default:
	bad_packet:
		FR_STATS_INC(auth, total_unknown_types);

		DEBUG("Invalid packet code %d sent from client %s port %d : IGNORED",
		      packet->code, client->shortname, packet->src_port);
		rad_free(&sock->packet);
		return 0;
	}
