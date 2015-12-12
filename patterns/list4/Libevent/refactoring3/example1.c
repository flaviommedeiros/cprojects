switch (proto) {
	case 0:
		return NULL;
	case IPPROTO_TCP:
		return "tcp";
	case IPPROTO_UDP:
		return "udp";
#ifdef IPPROTO_SCTP
	case IPPROTO_SCTP:
		return "sctp";
#endif
	default:
#ifdef EVENT__HAVE_GETPROTOBYNUMBER
		{
			struct protoent *ent = getprotobynumber(proto);
			if (ent)
				return ent->p_name;
		}
#endif
		return NULL;
	}
