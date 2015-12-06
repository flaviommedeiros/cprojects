#ifdef RB_IPV6
if (request->addr.ss_family == AF_INET6)
				gethost_byname_type(request->name, request->query, T_AAAA);
			else
#endif
				gethost_byname_type(request->name, request->query, T_A);
