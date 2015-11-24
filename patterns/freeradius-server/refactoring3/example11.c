switch (packet->code) {
	case PW_CODE_ACCESS_ACCEPT:
	case PW_CODE_ACCESS_CHALLENGE:
	case PW_CODE_ACCESS_REJECT:
		break;

#  ifdef WITH_ACCOUNTING
	case PW_CODE_ACCOUNTING_RESPONSE:
		break;
#  endif

#  ifdef WITH_COA
	case PW_CODE_DISCONNECT_ACK:
	case PW_CODE_DISCONNECT_NAK:
	case PW_CODE_COA_ACK:
	case PW_CODE_COA_NAK:
		break;
#  endif

	default:
		/*
		 *	FIXME: Update MIB for packet types?
		 */
		ERROR("Invalid packet code %d sent to a proxy port from home server %s port %d - ID %d : IGNORED",
		      packet->code,
		      fr_inet_ntoh(&packet->src_ipaddr, buffer, sizeof(buffer)),
		      packet->src_port, packet->id);
#  ifdef WITH_STATS
		listener->stats.total_unknown_types++;
#  endif
		rad_free(&packet);
		return 0;
	}
