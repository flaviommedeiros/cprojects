#ifdef USE_SSL
if (conn->ssl)
	{
		int			err;

		DISABLE_SIGPIPE(conn, spinfo, return -1);

		SOCK_ERRNO_SET(0);
		n = SSL_write(conn->ssl, ptr, len);
		err = SSL_get_error(conn->ssl, n);
		switch (err)
		{
			case SSL_ERROR_NONE:
				if (n < 0)
				{
					/* Not supposed to happen, so we don't translate the msg */
					printfPQExpBuffer(&conn->errorMessage,
									  "SSL_write failed but did not provide error information\n");
					/* assume the connection is broken */
					result_errno = ECONNRESET;
				}
				break;
			case SSL_ERROR_WANT_READ:

				/*
				 * Returning 0 here causes caller to wait for write-ready,
				 * which is not really the right thing, but it's the best we
				 * can do.
				 */
				n = 0;
				break;
			case SSL_ERROR_WANT_WRITE:
				n = 0;
				break;
			case SSL_ERROR_SYSCALL:
				if (n < 0)
				{
					result_errno = SOCK_ERRNO;
					REMEMBER_EPIPE(spinfo, result_errno == EPIPE);
					if (result_errno == EPIPE ||
						result_errno == ECONNRESET)
						printfPQExpBuffer(&conn->errorMessage,
										  libpq_gettext(
								"server closed the connection unexpectedly\n"
														"\tThis probably means the server terminated abnormally\n"
							 "\tbefore or while processing the request.\n"));
					else
						printfPQExpBuffer(&conn->errorMessage,
									libpq_gettext("SSL SYSCALL error: %s\n"),
										  SOCK_STRERROR(result_errno,
													  sebuf, sizeof(sebuf)));
				}
				else
				{
					printfPQExpBuffer(&conn->errorMessage,
						 libpq_gettext("SSL SYSCALL error: EOF detected\n"));
					/* assume the connection is broken */
					result_errno = ECONNRESET;
					n = -1;
				}
				break;
			case SSL_ERROR_SSL:
				{
					char	   *errm = SSLerrmessage();

					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext("SSL error: %s\n"), errm);
					SSLerrfree(errm);
					/* assume the connection is broken */
					result_errno = ECONNRESET;
					n = -1;
					break;
				}
			case SSL_ERROR_ZERO_RETURN:

				/*
				 * Per OpenSSL documentation, this error code is only returned
				 * for a clean connection closure, so we should not report it
				 * as a server crash.
				 */
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("SSL connection has been closed unexpectedly\n"));
				result_errno = ECONNRESET;
				n = -1;
				break;
			default:
				printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("unrecognized SSL error code: %d\n"),
								  err);
				/* assume the connection is broken */
				result_errno = ECONNRESET;
				n = -1;
				break;
		}
	}
	else
#endif   /* USE_SSL */
	{
		int			flags = 0;

#ifdef MSG_NOSIGNAL
		if (conn->sigpipe_flag)
			flags |= MSG_NOSIGNAL;

retry_masked:
#endif   /* MSG_NOSIGNAL */

		DISABLE_SIGPIPE(conn, spinfo, return -1);

		n = send(conn->sock, ptr, len, flags);

		if (n < 0)
		{
			result_errno = SOCK_ERRNO;

			/*
			 * If we see an EINVAL, it may be because MSG_NOSIGNAL isn't
			 * available on this machine.  So, clear sigpipe_flag so we don't
			 * try the flag again, and retry the send().
			 */
#ifdef MSG_NOSIGNAL
			if (flags != 0 && result_errno == EINVAL)
			{
				conn->sigpipe_flag = false;
				flags = 0;
				goto retry_masked;
			}
#endif   /* MSG_NOSIGNAL */

			/* Set error message if appropriate */
			switch (result_errno)
			{
#ifdef EAGAIN
				case EAGAIN:
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
				case EWOULDBLOCK:
#endif
				case EINTR:
					/* no error message, caller is expected to retry */
					break;

				case EPIPE:
					/* Set flag for EPIPE */
					REMEMBER_EPIPE(spinfo, true);
					/* FALL THRU */

#ifdef ECONNRESET
				case ECONNRESET:
#endif
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext(
								"server closed the connection unexpectedly\n"
					"\tThis probably means the server terminated abnormally\n"
							 "\tbefore or while processing the request.\n"));
					break;

				default:
					printfPQExpBuffer(&conn->errorMessage,
						libpq_gettext("could not send data to server: %s\n"),
									  SOCK_STRERROR(result_errno,
													sebuf, sizeof(sebuf)));
					break;
			}
		}
	}
