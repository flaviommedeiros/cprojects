switch (addr.ss.ss_family)
    {
      case AF_INET:
	*port = ntohs(addr.sin.sin_port);
	break;

#ifdef AF_INET6
      case AF_INET6:
	*port = ntohs(addr.sin6.sin6_port);
	break;
#endif

      default:
	free(*address);
	address = NULL;

	event_err(1, "%s: unhandled address family\n", __func__);
	return;
    }
