#ifdef USE_SSL
if (conn->ssl)
	{
		int			err;

		DECLARE_SIGPIPE_INFO(spinfo);

		/* SSL_read can write to the socket, so we need to disable SIGPIPE */
		DISABLE_SIGPIPE(conn, spinfo, return -1);

rloop:
		SOCK_ERRNO_SET(0);
		n = SSL_read(conn->ssl, ptr, len);
		err = SSL_get_error(conn->ssl, n);
		switch (err)
		{
			case SSL_ERROR_NONE:
				if (n < 0)
				{
					/* Not supposed to happen, so we don't translate the msg */
					printfPQExpBuffer(&conn->errorMessage,
									  "SSL_read failed but did not provide error information\n");
					/* assume the connection is broken */
					result_errno = ECONNRESET;
				}
				break;
			case SSL_ERROR_WANT_READ:
				n = 0;
				break;
			case SSL_ERROR_WANT_WRITE:

				/*
				 * Returning 0 here would cause caller to wait for read-ready,
				 * which is not correct since what SSL wants is wait for
				 * write-ready.  The former could get us stuck in an infinite
				 * wait, so don't risk it; busy-loop instead.
				 */
				goto rloop;
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

		RESTORE_SIGPIPE(conn, spinfo);
	}
	else
#endif   /* USE_SSL */
	{
		n = recv(conn->sock, ptr, len, 0);

		if (n < 0)
		{
			result_errno = SOCK_ERRNO;

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

#ifdef ECONNRESET
				case ECONNRESET:
					printfPQExpBuffer(&conn->errorMessage,
									  libpq_gettext(
								"server closed the connection unexpectedly\n"
					"\tThis probably means the server terminated abnormally\n"
							 "\tbefore or while processing the request.\n"));
					break;
#endif

				default:
					printfPQExpBuffer(&conn->errorMessage,
					libpq_gettext("could not receive data from server: %s\n"),
									  SOCK_STRERROR(result_errno,
													sebuf, sizeof(sebuf)));
					break;
			}
		}
	}
