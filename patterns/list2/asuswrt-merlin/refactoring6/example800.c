if (!(errno == EINPROGRESS || errno == EALREADY ||
#ifdef EISCONN
	      errno == EISCONN ||
#endif
	      errno == EAGAIN || errno == EINTR)) {
		state->sys_errno = errno;
		goto post_errno;
	}
