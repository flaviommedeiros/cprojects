if (!tried_reset && (errno == EAGAIN
#ifdef EWOULDBLOCK
				     || errno == EWOULDBLOCK
#endif /* EWOULDBLOCK */
				    ))
		{
			int oerrno = errno;
			if (reset_nonblock(fd) > 0) {
				tried_reset = 1;
				continue;
			}
			errno = oerrno;
		}
