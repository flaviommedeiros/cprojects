switch (sig) {
	case SIGHUP:
		printf ("Handling Graceful Restart..\n");
		cherokee_server_handle_HUP (srv);
		break;

	case SIGUSR2:
		printf ("Reopening log files..\n");
		cherokee_server_log_reopen (srv);
		break;

	case SIGINT:
	case SIGTERM:
		if (srv->wanna_exit) {
			break;
		}

		printf ("Server is exiting..\n");
		cherokee_server_handle_TERM (srv);
		break;

	case SIGCHLD:
		wait_process (si->si_pid);
		break;

	case SIGSEGV:
#ifdef SIGBUS
	case SIGBUS:
#endif
		cherokee_server_handle_panic (srv);
		break;

	default:
		PRINT_ERROR ("Unknown signal: %d\n", sig);
	}
