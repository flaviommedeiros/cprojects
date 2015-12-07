if (ifa->ifa_addr->sa_family == AF_INET)     v4Loopback = ifa;
#ifndef NO_IPV6
							else if (sin6->sin6_addr.s6_addr[0] != 0xFD) v6Loopback = ifa;
#endif
