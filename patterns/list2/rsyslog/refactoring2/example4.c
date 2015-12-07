#if defined(EPOLL_CLOEXEC) && defined(HAVE_EPOLL_CREATE1)
if(efd < 0 && errno == ENOSYS)
#endif
	{
		DBGPRINTF("imudp uses epoll_create()\n");
		efd = epoll_create(NUM_EPOLL_EVENTS);
	}
