switch (af) {
    case AF_INET : {
	struct sockaddr_in *sin4 = (struct sockaddr_in *)sa;

	memset (sin4, 0, sizeof(*sin4));
	sin4->sin_family = AF_INET;
	sin4->sin_port   = 0;
	sin4->sin_addr.s_addr = INADDR_ANY;
	break;
    }
#ifdef HAVE_IPV6
    case AF_INET6 : {
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;

	memset (sin6, 0, sizeof(*sin6));
	sin6->sin6_family = AF_INET6;
	sin6->sin6_port   = 0;
	sin6->sin6_addr   = in6addr_any;
	break;
    }
#endif
    default :
	errx (1, "unknown address family %d", sa->sa_family);
	break;
    }
