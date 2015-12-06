switch (a->type)
	{
	case NA_BROADCAST:
		((struct sockaddr_in *)s)->sin_family      = AF_INET;
		((struct sockaddr_in *)s)->sin_port        = a->port;
		((struct sockaddr_in *)s)->sin_addr.s_addr = INADDR_BROADCAST;
		break;
	case NA_IP:
		((struct sockaddr_in *)s)->sin_family      = AF_INET;
		((struct sockaddr_in *)s)->sin_addr.s_addr = *(int *)&a->ip;
		((struct sockaddr_in *)s)->sin_port        = a->port;
		break;
#ifdef FEATURE_IPV6
	case NA_IP6:
		((struct sockaddr_in6 *)s)->sin6_family   = AF_INET6;
		((struct sockaddr_in6 *)s)->sin6_addr     = *((struct in6_addr *) &a->ip6);
		((struct sockaddr_in6 *)s)->sin6_port     = a->port;
		((struct sockaddr_in6 *)s)->sin6_scope_id = a->scope_id;
		break;
	case NA_MULTICAST6:
		((struct sockaddr_in6 *)s)->sin6_family = AF_INET6;
		((struct sockaddr_in6 *)s)->sin6_addr   = curgroup.ipv6mr_multiaddr;
		((struct sockaddr_in6 *)s)->sin6_port   = a->port;
		break;
#endif
	default:
		Com_Printf("NetadrToSockadr: bad address type\n");
		break;
	}
