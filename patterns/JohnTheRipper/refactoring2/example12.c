#ifndef HAVE_MPI
if (john_main_process)
#endif
	{
		int c;
#if OS_FORK
		int new_abort = 0, new_status = 0;
#endif
		while ((c = tty_getchar()) >= 0) {
			if (c == 3 || c == 'q') {
#if OS_FORK
				new_abort = 1;
#endif
				sig_handle_abort(0);
			} else {
#if OS_FORK
				new_status = 1;
#endif
				event_status = event_pending = 1;
			}
		}

#if OS_FORK
		if (new_abort || new_status)
			signal_children(new_abort ? SIGTERM : SIGUSR1);
#endif
	}
