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
