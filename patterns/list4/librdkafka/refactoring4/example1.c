#ifdef EAI_SYSTEM
if (r == EAI_SYSTEM)
#else
		if (0)
#endif
			*errstr = rd_strerror(errno);
		else {
#ifdef _MSC_VER
			*errstr = gai_strerrorA(r);
#else
			*errstr = gai_strerror(r);
#endif
			errno = EFAULT;
		}
