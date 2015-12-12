switch (hdr->nflog_family) {

	case AF_INET:
		ip_print(ndo, p, length);
		break;

#ifdef AF_INET6
	case AF_INET6:
		ip6_print(ndo, p, length);
		break;
#endif /* AF_INET6 */

	default:
		if (!ndo->ndo_eflag)
			nflog_hdr_print(ndo, hdr,
				length + sizeof(nflog_hdr_t));

		if (!ndo->ndo_suppress_default_print)
			ND_DEFAULTPRINT(p, caplen);
		break;
	}
