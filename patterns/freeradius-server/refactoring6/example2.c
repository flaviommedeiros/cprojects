if ((fr_set_signal(SIGINT, sig_fatal) < 0)
#ifdef SIGQUIT
		|| (fr_set_signal(SIGQUIT, sig_fatal) < 0)
#endif
		) {
			ERROR("%s", fr_strerror());
			exit(EXIT_FAILURE);
		}
