switch (sig) {
	case SIGALRM:
		fetchRestartCalls = 0;
		sigalrm = 1;
		break;
#ifdef SIGINFO
	case SIGINFO:
		siginfo = 1;
		break;
#endif
	case SIGINT:
		fetchRestartCalls = 0;
		sigint = 1;
		break;
	}
