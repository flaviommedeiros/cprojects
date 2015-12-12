switch (areq)
	{
		case AUTH_REQ_OK:
			break;

		case AUTH_REQ_KRB4:
			printfPQExpBuffer(&conn->errorMessage,
				 libpq_gettext("Kerberos 4 authentication not supported\n"));
			return STATUS_ERROR;

		case AUTH_REQ_KRB5:
			printfPQExpBuffer(&conn->errorMessage,
				 libpq_gettext("Kerberos 5 authentication not supported\n"));
			return STATUS_ERROR;

#if defined(ENABLE_GSS) || defined(ENABLE_SSPI)
		case AUTH_REQ_GSS:
#if !defined(ENABLE_SSPI)
			/* no native SSPI, so use GSSAPI library for it */
		case AUTH_REQ_SSPI:
#endif
			{
				int			r;

				pglock_thread();

				/*
				 * If we have both GSS and SSPI support compiled in, use SSPI
				 * support by default. This is overridable by a connection
				 * string parameter. Note that when using SSPI we still leave
				 * the negotiate parameter off, since we want SSPI to use the
				 * GSSAPI kerberos protocol. For actual SSPI negotiate
				 * protocol, we use AUTH_REQ_SSPI.
				 */
#if defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				if (conn->gsslib && (pg_strcasecmp(conn->gsslib, "gssapi") == 0))
					r = pg_GSS_startup(conn);
				else
					r = pg_SSPI_startup(conn, 0);
#elif defined(ENABLE_GSS) && !defined(ENABLE_SSPI)
				r = pg_GSS_startup(conn);
#elif !defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				r = pg_SSPI_startup(conn, 0);
#endif
				if (r != STATUS_OK)
				{
					/* Error message already filled in. */
					pgunlock_thread();
					return STATUS_ERROR;
				}
				pgunlock_thread();
			}
			break;

		case AUTH_REQ_GSS_CONT:
			{
				int			r;

				pglock_thread();
#if defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				if (conn->usesspi)
					r = pg_SSPI_continue(conn);
				else
					r = pg_GSS_continue(conn);
#elif defined(ENABLE_GSS) && !defined(ENABLE_SSPI)
				r = pg_GSS_continue(conn);
#elif !defined(ENABLE_GSS) && defined(ENABLE_SSPI)
				r = pg_SSPI_continue(conn);
#endif
				if (r != STATUS_OK)
				{
					/* Error message already filled in. */
					pgunlock_thread();
					return STATUS_ERROR;
				}
				pgunlock_thread();
			}
			break;
#else							/* defined(ENABLE_GSS) || defined(ENABLE_SSPI) */
			/* No GSSAPI *or* SSPI support */
		case AUTH_REQ_GSS:
		case AUTH_REQ_GSS_CONT:
			printfPQExpBuffer(&conn->errorMessage,
					 libpq_gettext("GSSAPI authentication not supported\n"));
			return STATUS_ERROR;
#endif   /* defined(ENABLE_GSS) || defined(ENABLE_SSPI) */

#ifdef ENABLE_SSPI
		case AUTH_REQ_SSPI:

			/*
			 * SSPI has it's own startup message so libpq can decide which
			 * method to use. Indicate to pg_SSPI_startup that we want SSPI
			 * negotiation instead of Kerberos.
			 */
			pglock_thread();
			if (pg_SSPI_startup(conn, 1) != STATUS_OK)
			{
				/* Error message already filled in. */
				pgunlock_thread();
				return STATUS_ERROR;
			}
			pgunlock_thread();
			break;
#else

			/*
			 * No SSPI support. However, if we have GSSAPI but not SSPI
			 * support, AUTH_REQ_SSPI will have been handled in the codepath
			 * for AUTH_REQ_GSSAPI above, so don't duplicate the case label in
			 * that case.
			 */
#if !defined(ENABLE_GSS)
		case AUTH_REQ_SSPI:
			printfPQExpBuffer(&conn->errorMessage,
					   libpq_gettext("SSPI authentication not supported\n"));
			return STATUS_ERROR;
#endif   /* !define(ENABLE_GSSAPI) */
#endif   /* ENABLE_SSPI */


		case AUTH_REQ_CRYPT:
			printfPQExpBuffer(&conn->errorMessage,
					  libpq_gettext("Crypt authentication not supported\n"));
			return STATUS_ERROR;

		case AUTH_REQ_MD5:
		case AUTH_REQ_PASSWORD:
			conn->password_needed = true;
			if (conn->pgpass == NULL || conn->pgpass[0] == '\0')
			{
				printfPQExpBuffer(&conn->errorMessage,
								  PQnoPasswordSupplied);
				return STATUS_ERROR;
			}
			if (pg_password_sendauth(conn, conn->pgpass, areq) != STATUS_OK)
			{
				printfPQExpBuffer(&conn->errorMessage,
					 "fe_sendauth: error sending password authentication\n");
				return STATUS_ERROR;
			}
			break;

		case AUTH_REQ_SCM_CREDS:
			if (pg_local_sendauth(conn) != STATUS_OK)
				return STATUS_ERROR;
			break;

		default:
			printfPQExpBuffer(&conn->errorMessage,
			libpq_gettext("authentication method %u not supported\n"), areq);
			return STATUS_ERROR;
	}
