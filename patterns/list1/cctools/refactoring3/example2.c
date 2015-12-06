switch (rc) {
		case 0: /* no error */
			break;
		/* Transient errors. */
#ifdef ECONNRESET
		case ECONNRESET:
#endif
#ifdef ETIMEDOUT
		case ETIMEDOUT:
#endif
		case EAGAIN: /* This is either a SQL database lock error or the Chirp server is busy (also with a locked Job database). */
		case EINTR: /* Temporary error. */
			break;
		/* Permanent connection failures. */
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
		case ESRCH: /* somehow the job was lost on the remote Chirp server, probably Job DB got wiped? */
		case EIO: /* Internal Confuga error. */
			reschedule(C, id, tag, rc);
			break;
		default:
			fail(C, id, tag, strerror(rc));
			break;
	}
