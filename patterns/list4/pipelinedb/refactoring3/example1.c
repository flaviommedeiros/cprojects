switch (addr->sa_family)
	{
		case AF_INET:
			len = sizeof(struct sockaddr_in);
			break;
#ifdef HAVE_IPV6
		case AF_INET6:
			len = sizeof(struct sockaddr_in6);
			break;
#endif
		default:
			len = sizeof(struct sockaddr_storage);
			break;
	}
