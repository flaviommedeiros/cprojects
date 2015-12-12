if(sa->sa_family == AF_INET6
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
