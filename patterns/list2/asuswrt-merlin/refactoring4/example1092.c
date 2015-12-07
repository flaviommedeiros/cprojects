#if defined(RLIM_INFINITY)
if(rlp.rlim_cur == RLIM_INFINITY)
		return saved_current_limit;
