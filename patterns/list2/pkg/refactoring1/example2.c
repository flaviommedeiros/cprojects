if (laddr->ai_family == AF_INET) {
			rip = (char *)&((struct sockaddr_in *)(void *)
			    raddr->ai_addr)->sin_addr.s_addr;
			ret = fetch_ssl_ipaddr_match_bin(laddr, rip, 4);
#ifdef INET6
		} else if (laddr->ai_family == AF_INET6) {
			rip = (char *)&((struct sockaddr_in6 *)(void *)
			    raddr->ai_addr)->sin6_addr;
			ret = fetch_ssl_ipaddr_match_bin(laddr, rip, 16);
#endif
		}
#endif
