switch (sa->sa_family) {
    case AF_INET : {
	struct sockaddr_in *sin4 = (struct sockaddr_in *)sa;
	sin4->sin_port = port;
	break;
    }
#ifdef HAVE_IPV6
    case AF_INET6 : {
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
	sin6->sin6_port = port;
	break;
    }
#endif
    default :
	errx (1, "unknown address family %d", sa->sa_family);
	break;
    }
