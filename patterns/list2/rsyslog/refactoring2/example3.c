#	if defined(EPOLL_CLOEXEC) && defined(HAVE_EPOLL_CREATE1)
if(epollfd < 0 && errno == ENOSYS)
#	endif
	{
		DBGPRINTF("imptcp uses epoll_create()\n");
		/* reading the docs, the number of epoll events passed to
		 * epoll_create() seems not to be used at all in kernels. So
		 * we just provide "a" number, happens to be 10.
		 */
		epollfd = epoll_create(10);
	}
