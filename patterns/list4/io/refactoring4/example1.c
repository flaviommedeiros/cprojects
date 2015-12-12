#ifdef WIN32
if (ioctlsocket(self->fd, FIONBIO, &nonzero) == -1)
#else
	SocketResetErrorStatus();
