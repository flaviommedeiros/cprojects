if (ret == EINTR ||
#ifdef ETIME
	    ret == ETIME ||
#endif
	    ret == ETIMEDOUT)
		ret = 0;
