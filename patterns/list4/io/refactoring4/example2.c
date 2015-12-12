#ifdef WIN32
if (ioctlsocket((SOCKET_DESCRIPTOR) fd, FIONREAD, &iToRead) == SOCKET_ERROR && SocketErrorStatus() == WSAENOTSOCK)
#else
	if (fcntl(fd, F_GETFL, NULL) == -1)
#endif
	{
		return 0;
	}
