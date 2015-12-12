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
