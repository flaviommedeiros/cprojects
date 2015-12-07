switch (gai_afdl[i].a_af) {
			case AF_INET:
				v4a = ((struct in_addr *)pton)->s_addr;
				v4a = ntohl(v4a);
				if (IN_MULTICAST(v4a) || IN_EXPERIMENTAL(v4a))
					pai->ai_flags &= ~AI_CANONNAME;
				v4a >>= IN_CLASSA_NSHIFT;
				if (v4a == 0 || v4a == IN_LOOPBACKNET)
					pai->ai_flags &= ~AI_CANONNAME;
				break;
#ifdef ENABLE_IPV6
			case AF_INET6:
				pfx = ((struct in6_addr *)pton)->s6_addr8[0];
				if (pfx == 0 || pfx == 0xfe || pfx == 0xff)
					pai->ai_flags &= ~AI_CANONNAME;
				break;
#endif
			}
