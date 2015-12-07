#if defined(EPOLL_CLOEXEC) && defined(HAVE_EPOLL_CREATE1)
if(pThis->efd < 0 && errno == ENOSYS)
#endif
	{
		DBGPRINTF("nsdpoll_ptcp uses epoll_create()\n");
		pThis->efd = epoll_create(100); /* size is ignored in newer kernels, but 100 is not bad... */
	}
