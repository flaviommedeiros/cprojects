#if defined(HAVE_FUTIMENS) && !defined(__CYGWIN__)
if (futimens(fd, timespecs) == 0)
		return (close(fd));
