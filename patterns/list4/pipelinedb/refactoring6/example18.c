if ((shmdt(UsedShmemSegAddr) < 0)
#if defined(EXEC_BACKEND) && defined(__CYGWIN__)
		/* Work-around for cygipc exec bug */
			&& shmdt(NULL) < 0
#endif
			)
			elog(LOG, "shmdt(%p) failed: %m", UsedShmemSegAddr);
