#ifdef USE_IOVEC
while (writev(2, iov, 8) == -1 && errno == EAGAIN)
	    continue;
