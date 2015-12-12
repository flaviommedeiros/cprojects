switch (af) {

		case AF_INET:
#if OPENBSD_AF_INET != AF_INET
		case OPENBSD_AF_INET:		/* XXX: read pcap files */
#endif
		        ip_print(ndo, p, length);
			break;

#if defined(AF_INET6) || defined(OPENBSD_AF_INET6)
#ifdef AF_INET6
		case AF_INET6:
#endif /* AF_INET6 */
#if !defined(AF_INET6) || OPENBSD_AF_INET6 != AF_INET6
		case OPENBSD_AF_INET6:		/* XXX: read pcap files */
#endif /* !defined(AF_INET6) || OPENBSD_AF_INET6 != AF_INET6 */
			ip6_print(ndo, p, length);
			break;
#endif /* defined(AF_INET6) || defined(OPENBSD_AF_INET6) */

	default:
		/* address family not handled, print raw packet */
		if (!ndo->ndo_eflag)
			pflog_print(ndo, hdr);
		if (!ndo->ndo_suppress_default_print)
			ND_DEFAULTPRINT(p, caplen);
	}
