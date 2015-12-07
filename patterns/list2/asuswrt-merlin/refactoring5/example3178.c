#ifdef HAVE_IPV6
if (local_addr->sa.sa_family == AF_INET6)
				local.addr.addr6 = local_addr->in6.sin6_addr;
			      else
#endif
				local.addr.addr4 = local_addr->in.sin_addr;
