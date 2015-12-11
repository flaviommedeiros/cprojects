if (connect(iscsi->fd, &sa.sa, socksize) != 0
#if defined(WIN32)
	    && WSAGetLastError() != WSAEWOULDBLOCK) {
#else
	    && errno != EINPROGRESS) {
#endif
		iscsi_set_error(iscsi, "Connect failed with errno : "
				"%s(%d)", strerror(errno), errno);
		close(iscsi->fd);
		iscsi->fd = -1;
		freeaddrinfo(ai);
		return -1;
	}
