switch (error) {
		case EAGAIN:
			/* This is either a SQL database lock error or the Chirp server is busy (also with a locked Job database). */
			break;
		case EINTR:
			/* temporary error */
			break;
#ifdef ECONNRESET
		case ECONNRESET:
			break;
#endif
#ifdef ETIMEDOUT
		case ETIMEDOUT:
			break;
#endif
		case ESRCH:
			/* somehow the job was lost on the remote Chirp server, probably Job DB got wiped? */
#ifdef EADDRNOTAVAIL
		case EADDRNOTAVAIL:
#endif
#ifdef ECONNABORTED
		case ECONNABORTED:
#endif
#ifdef ECONNREFUSED
		case ECONNREFUSED:
#endif
#ifdef EHOSTUNREACH
		case EHOSTUNREACH:
#endif
#ifdef ENETDOWN
		case ENETDOWN:
#endif
#ifdef ENETRESET
		case ENETRESET:
#endif
#ifdef ENETUNREACH
		case ENETUNREACH:
#endif
			//reschedule(C, id, error);
			//break;
		default:
			fail(C, id, strerror(error));
			break;
	}
