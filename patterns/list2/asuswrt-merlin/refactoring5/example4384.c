#ifdef HAVE_LIBSSL
if (!sd->ssl) {
#endif
		while (len > 0) {
			size_t sendSize = (len > blocklen) ? blocklen : len;
			bytes = send(sd->sock, buf, sendSize, 0);
			if (bytes == -1) {
				if (errno == EAGAIN) {
					continue;
				} else if (errno == EINTR) {
					continue;
				} else {
					sd->flags |= SOCKET_ERROR;
					sd->errnum = errno;
					break;
				}
			} else if (bytes == 0) {
				sd->flags |= SOCKET_ERROR;
				sd->errnum = EPIPE;
				break;
			} else if (bytes > 0) {
				buf += bytes;
				len -= bytes;
				sentLen += bytes;
			}
		}
#ifdef HAVE_LIBSSL
	} else {
		sentLen = SSL_write(sd->ssl, buf, len);
	}
