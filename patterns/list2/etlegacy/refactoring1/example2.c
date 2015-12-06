if (s->sa_family == AF_INET)
	{
		a->type        = NA_IP;
		*(int *)&a->ip = ((struct sockaddr_in *)s)->sin_addr.s_addr;
		a->port        = ((struct sockaddr_in *)s)->sin_port;
	}
#ifdef FEATURE_IPV6
	else if (s->sa_family == AF_INET6)
	{
		a->type = NA_IP6;
		memcpy(a->ip6, &((struct sockaddr_in6 *)s)->sin6_addr, sizeof(a->ip6));
		a->port     = ((struct sockaddr_in6 *)s)->sin6_port;
		a->scope_id = ((struct sockaddr_in6 *)s)->sin6_scope_id;
	}
#endif
