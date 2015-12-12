switch (beentry->st_clientaddr.addr.ss_family)
	{
		case AF_INET:
#ifdef HAVE_IPV6
		case AF_INET6:
#endif
			break;
		case AF_UNIX:
			PG_RETURN_INT32(-1);
		default:
			PG_RETURN_NULL();
	}
