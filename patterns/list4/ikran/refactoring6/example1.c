if ((host1->h_addrtype != AF_INET)
#ifdef AF_LOCAL
			&& (host1->h_addrtype != AF_LOCAL)
#endif
			)
			continue;
