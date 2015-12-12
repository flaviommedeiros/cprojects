switch(ai->ai_family) {
#ifdef IP_ADD_MEMBERSHIP
		case AF_INET: {
			struct ip_mreq mreq;
			struct sockaddr_in in;
			memcpy(&in, ai->ai_addr, sizeof in);
			mreq.imr_multiaddr.s_addr = in.sin_addr.s_addr;
			mreq.imr_interface.s_addr = htonl(INADDR_ANY);
			if(setsockopt(device_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mreq, sizeof mreq)) {
				logger(LOG_ERR, "Cannot join multicast group %s %s: %s", host, port, sockstrerror(sockerrno));
				closesocket(device_fd);
				free(host);
				return false;
			}
#ifdef IP_MULTICAST_LOOP
			setsockopt(device_fd, IPPROTO_IP, IP_MULTICAST_LOOP, (const void *)&one, sizeof one);
#endif
#ifdef IP_MULTICAST_TTL
			setsockopt(device_fd, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&ttl, sizeof ttl);
#endif
		} break;
#endif

#ifdef IPV6_JOIN_GROUP
		case AF_INET6: {
			struct ipv6_mreq mreq;
			struct sockaddr_in6 in6;
			memcpy(&in6, ai->ai_addr, sizeof in6);
			memcpy(&mreq.ipv6mr_multiaddr, &in6.sin6_addr, sizeof mreq.ipv6mr_multiaddr);
			mreq.ipv6mr_interface = in6.sin6_scope_id;
			if(setsockopt(device_fd, IPPROTO_IPV6, IPV6_JOIN_GROUP, (void *)&mreq, sizeof mreq)) {
				logger(LOG_ERR, "Cannot join multicast group %s %s: %s", host, port, sockstrerror(sockerrno));
				closesocket(device_fd);
				free(host);
				return false;
			}
#ifdef IPV6_MULTICAST_LOOP
			setsockopt(device_fd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (const void *)&one, sizeof one);
#endif
#ifdef IPV6_MULTICAST_HOPS
			setsockopt(device_fd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (void *)&ttl, sizeof ttl);
#endif
		} break;
#endif
	
		default:
			logger(LOG_ERR, "Multicast for address family %x unsupported", ai->ai_family);
			closesocket(device_fd);
			free(host);
			return false;
	}
