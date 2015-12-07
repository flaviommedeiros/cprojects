if (errno == EINPROGRESS || errno == EALREADY ||
#ifdef EISCONN
			errno == EISCONN ||
#endif
		    errno == EAGAIN || errno == EINTR) {
			/* These are the error messages that something is
			   progressing. */
			good_connect = true;
		} else if (errno != 0) {
			/* There was a direct error */
			close(sockets[i]);
			sockets[i] = -1;
		}
