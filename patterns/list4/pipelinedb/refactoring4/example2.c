#ifdef WIN32
if (pstate->parallelSlot[i].threadId == GetCurrentThreadId())
#else
		if (pstate->parallelSlot[i].pid == getpid())
#endif
			return &(pstate->parallelSlot[i]);
