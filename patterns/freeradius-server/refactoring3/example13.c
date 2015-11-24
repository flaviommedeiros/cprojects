switch (packet->code) {
	case PW_CODE_ACCESS_ACCEPT:
	case PW_CODE_ACCESS_CHALLENGE:
	case PW_CODE_ACCESS_REJECT:
		break;

#    ifdef WITH_ACCOUNTING
	case PW_CODE_ACCOUNTING_RESPONSE:
		break;
#    endif

	default:
		/*
		 *	FIXME: Update MIB for packet types?
		 */
		ERROR("Invalid packet code %d sent to a proxy port "
		       "from home server %s port %d - ID %d : IGNORED",
		       packet->code,
		       fr_inet_ntoh(&packet->src_ipaddr, buffer, sizeof(buffer)),
		       packet->src_port, packet->id);
		rad_free(&packet);
		return 0;
	}
