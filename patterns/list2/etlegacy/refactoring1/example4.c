if (search->ai_family == AF_INET)
			{
				NET_AddLocalAddress("", search->ai_addr, (struct sockaddr *) &mask4);
			}
#ifdef FEATURE_IPV6
			else if (search->ai_family == AF_INET6)
			{
				NET_AddLocalAddress("", search->ai_addr, (struct sockaddr *) &mask6);
			}
#endif
