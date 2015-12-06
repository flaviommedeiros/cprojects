#ifdef SUPPORT_IP6
if (addr->sa_family == AF_INET6) {
	s = socket (PF_INET6, SOCK_STREAM, IPPROTO_TCP);
	addrlen = sizeof (struct sockaddr_in6);
    }
    else
#endif
    {
	s = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
	addrlen = sizeof (struct sockaddr_in);
    }
