#ifdef EWOULDBLOCK
if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
#else
			if (errno == EINTR || errno == EAGAIN)
#endif
				continue;
