#ifndef NO_SSL
if (ssl != NULL) {
			n = SSL_write(ssl, buf, len);
			if (n <= 0) {
				err = SSL_get_error(ssl, n);
				if ((err == 5 /* SSL_ERROR_SYSCALL */) && (n == -1)) {
					err = ERRNO;
				} else {
					DEBUG_TRACE("SSL_write() failed, error %d", err);
					return -1;
				}
			} else {
				err = 0;
			}
		} else
#endif
		    if (fp != NULL) {
			n = (int)fwrite(buf, 1, (size_t)len, fp);
			if (ferror(fp)) {
				n = -1;
				err = ERRNO;
			} else {
				err = 0;
			}
		} else {
			n = (int)send(sock, buf, (len_t)len, MSG_NOSIGNAL);
			err = (n < 0) ? ERRNO : 0;
		}
