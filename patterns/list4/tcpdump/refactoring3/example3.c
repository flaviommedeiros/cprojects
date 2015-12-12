switch (hdr->af) {
	case AF_INET:
		ip_print(ndo, p, length);
		break;
#ifdef AF_INET6
	case AF_INET6:
		ip6_print(ndo, p, length);
		break;
#endif
	}
