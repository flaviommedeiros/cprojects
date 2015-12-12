switch ((worker_pid = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
					(errmsg("could not fork worker process: %m")));
			return;

#ifndef EXEC_BACKEND
		case 0:
			#ifdef BACKTRACE_SEGFAULTS
				pqsignal(SIGSEGV, debug_segfault);
			#endif
			/* in postmaster child ... */
			/* Close the postmaster's sockets */
			ClosePostmasterPorts(false);

			/* Lose the postmaster's on-exit routines */
			on_exit_reset();

			/* Do NOT release postmaster's working memory context */

			MyBgworkerEntry = &rw->rw_worker;
			StartBackgroundWorker();
			break;
#endif
		default:
			rw->rw_pid = worker_pid;
			if (rw->rw_backend)
				rw->rw_backend->pid = rw->rw_pid;
			ReportBackgroundWorkerPID(rw);
	}
