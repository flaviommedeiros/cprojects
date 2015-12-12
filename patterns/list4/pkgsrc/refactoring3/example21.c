switch(sig) {
#ifdef SIGINFO
	case SIGINFO:
#endif
	case SIGQUIT:
	case SIGUSR1:
	case SIGUSR2:
	case SIGWINCH:
		restartable = 1;
		break;

	case SIGALRM:
	case SIGINT:
	case SIGPIPE:
		restartable = 0;
		break;

	default:
		/*
		 * This is unpleasant, but I don't know what would be better.
		 * Right now, this "can't happen"
		 */
		errx(1, "xsignal_restart: called with signal %d", sig);
	}
