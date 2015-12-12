#if defined(HAVE_GETUID) && defined(HAVE_GETEUID) && \
    defined(HAVE_GETGID) && defined(HAVE_GETEGID)
if (issetugid())
			return -1;
