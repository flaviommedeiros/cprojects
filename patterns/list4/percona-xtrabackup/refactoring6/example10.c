if (protocol
#ifdef AF_UNIX
		|| family != AF_UNIX
#endif
		) {
		EVUTIL_SET_SOCKET_ERROR(WSAEAFNOSUPPORT);
		return -1;
	}
