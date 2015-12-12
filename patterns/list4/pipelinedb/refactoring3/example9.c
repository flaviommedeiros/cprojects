switch ((pgStatPid = fork_process()))
#endif
	{
		case -1:
			ereport(LOG,
					(errmsg("could not fork statistics collector: %m")));
			return 0;

#ifndef EXEC_BACKEND
		case 0:
			/* in postmaster child ... */
			/* Close the postmaster's sockets */
			ClosePostmasterPorts(false);

			/* Lose the postmaster's on-exit routines */
			on_exit_reset();

			/* Drop our connection to postmaster's shared memory, as well */
			dsm_detach_all();
			PGSharedMemoryDetach();

			PgstatCollectorMain(0, NULL);
			break;
#endif

		default:
			return (int) pgStatPid;
	}
