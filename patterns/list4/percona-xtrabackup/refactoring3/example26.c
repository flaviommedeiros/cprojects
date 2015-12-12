switch (e) {
	case -1:		/* Make sure that the code is reachable */

#ifdef EWOULDBLOCK
	case EWOULDBLOCK:
#ifndef TRY_AGAIN
#define TRY_AGAIN
#endif
#endif /* EWOULDBLOCK */

#if defined(POSIX) && defined(EAGAIN)
#if defined(EWOULDBLOCK) && EWOULDBLOCK != EAGAIN
	case EAGAIN:
#ifndef TRY_AGAIN
#define TRY_AGAIN
#endif
#endif /* EWOULDBLOCK && EWOULDBLOCK != EAGAIN */
#endif /* POSIX && EAGAIN */

		e = 0;
#ifdef TRY_AGAIN
#if defined(F_SETFL) && defined(O_NDELAY)
		if ((e = fcntl(fd, F_GETFL, 0)) == -1)
			return -1;

		if (fcntl(fd, F_SETFL, e & ~O_NDELAY) == -1)
			return -1;
		else
			e = 1;
#endif /* F_SETFL && O_NDELAY */

#ifdef FIONBIO
		{
			int zero = 0;

			if (ioctl(fd, FIONBIO, &zero) == -1)
				return -1;
			else
				e = 1;
		}
#endif /* FIONBIO */

#endif /* TRY_AGAIN */
		return e ? 0 : -1;

	case EINTR:
		return 0;

	default:
		return -1;
	}
