#ifdef ENABLE_IPV6
if(ipv6) {
			struct sockaddr_in6 sockinfo;
			socklen_t len = sizeof(struct sockaddr_in6);
			if (getsockname(s, (struct sockaddr *)&sockinfo, &len) < 0) {
				syslog(LOG_ERR, "getsockname(): %m");
			} else {
				*port = ntohs(sockinfo.sin6_port);
			}
		} else {
#endif /* ENABLE_IPV6 */
			struct sockaddr_in sockinfo;
			socklen_t len = sizeof(struct sockaddr_in);
			if (getsockname(s, (struct sockaddr *)&sockinfo, &len) < 0) {
				syslog(LOG_ERR, "getsockname(): %m");
			} else {
				*port = ntohs(sockinfo.sin_port);
			}
#ifdef ENABLE_IPV6
		}
