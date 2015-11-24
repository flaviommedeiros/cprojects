#if __UNIX__
if (p->_maxfd)
		set_limit (p->_maxfd, RLIMIT_NOFILE, p->_maxfd);
