#ifndef WIN32
if (ret < 0 && errno != EINPROGRESS)
#else
	if (ret < 0 && WSAGetLastError() != WSAEWOULDBLOCK)
#endif
	{
		int old_errno = errno;
		close(handle);
		errno = old_errno;
		return NULL;
	}
