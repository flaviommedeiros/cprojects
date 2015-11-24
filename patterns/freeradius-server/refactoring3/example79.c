switch (a->af) {
	case AF_INET:
		return memcmp(&a->ipaddr.ip4addr,
			      &b->ipaddr.ip4addr,
			      sizeof(a->ipaddr.ip4addr));

#ifdef HAVE_STRUCT_SOCKADDR_IN6
	case AF_INET6:
		if (a->zone_id < b->zone_id) return -1;
		if (a->zone_id > b->zone_id) return +1;

		return memcmp(&a->ipaddr.ip6addr,
			      &b->ipaddr.ip6addr,
			      sizeof(a->ipaddr.ip6addr));
#endif

	default:
		break;
	}
