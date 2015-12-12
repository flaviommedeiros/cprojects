#ifdef USING_TIMERFD
if (epollop->timerfd >= 0) {
		struct itimerspec is;
		is.it_interval.tv_sec = 0;
		is.it_interval.tv_nsec = 0;
		if (tv == NULL) {
			/* No timeout; disarm the timer. */
			is.it_value.tv_sec = 0;
			is.it_value.tv_nsec = 0;
		} else {
			if (tv->tv_sec == 0 && tv->tv_usec == 0) {
				/* we need to exit immediately; timerfd can't
				 * do that. */
				timeout = 0;
			}
			is.it_value.tv_sec = tv->tv_sec;
			is.it_value.tv_nsec = tv->tv_usec * 1000;
		}
		/* TODO: we could avoid unnecessary syscalls here by only
		   calling timerfd_settime when the top timeout changes, or
		   when we're called with a different timeval.
		*/
		if (timerfd_settime(epollop->timerfd, 0, &is, NULL) < 0) {
			event_warn("timerfd_settime");
		}
	} else
#endif
	if (tv != NULL) {
		timeout = evutil_tv_to_msec_(tv);
		if (timeout < 0 || timeout > MAX_EPOLL_TIMEOUT_MSEC) {
			/* Linux kernels can wait forever if the timeout is
			 * too big; see comment on MAX_EPOLL_TIMEOUT_MSEC. */
			timeout = MAX_EPOLL_TIMEOUT_MSEC;
		}
	}
