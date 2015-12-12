if (gai->ai_addr->sa_family == AF_INET)
			{
				if (ipv4eq((struct sockaddr_in *) gai->ai_addr,
						   (struct sockaddr_in *) & port->raddr.addr))
				{
					found = true;
					break;
				}
			}
#ifdef HAVE_IPV6
			else if (gai->ai_addr->sa_family == AF_INET6)
			{
				if (ipv6eq((struct sockaddr_in6 *) gai->ai_addr,
						   (struct sockaddr_in6 *) & port->raddr.addr))
				{
					found = true;
					break;
				}
			}
#endif
