if(sa->sa_family == AF_INET
#if defined(__OpenBSD__)
				   || (sa->sa_family == 0 &&
				       sa->sa_len <= sizeof(struct sockaddr_in))
#endif
				   ) {
					uint32_t sin_addr = ntohl(((struct sockaddr_in *)sa)->sin_addr.s_addr);
					while((prefixlen < 32) &&
					      ((sin_addr & (1 << (31 - prefixlen))) != 0))
						prefixlen++;
				} else if(sa->sa_family == AF_INET6
#if defined(__OpenBSD__)
				          || (sa->sa_family == 0 &&
				              sa->sa_len == sizeof(struct sockaddr_in6))
#endif
				          ) {
					int i = 0;
					uint8_t * q =  ((struct sockaddr_in6 *)sa)->sin6_addr.s6_addr;
					while((*q == 0xff) && (i < 16)) {
						prefixlen += 8;
						q++; i++;
					}
					if(i < 16) {
						i = 0;
						while((i < 8) &&
						      ((*q & (1 << (7 - i))) != 0))
							i++;
						prefixlen += i;
					}
				}
