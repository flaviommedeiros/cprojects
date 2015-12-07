switch (af) {
#ifdef ENABLE_IPV6
		case AF_INET6:
			gai_afd = &gai_afdl[N_INET6];
			break;
#endif
#ifndef ENABLE_IPV6
		default:	/* AF_UNSPEC */
#endif
		case AF_INET:
			gai_afd = &gai_afdl[N_INET];
			break;
#ifdef ENABLE_IPV6
		default:	/* AF_UNSPEC */
			if (IN6_IS_ADDR_V4MAPPED((struct in6_addr *)ap)) {
				ap += sizeof(struct in6_addr) -
					sizeof(struct in_addr);
				gai_afd = &gai_afdl[N_INET];
			} else
				gai_afd = &gai_afdl[N_INET6];
			break;
#endif
		}
