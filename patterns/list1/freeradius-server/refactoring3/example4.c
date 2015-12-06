switch (sig) {
	case SIGTERM:
		radius_signal_self(RADIUS_SIGNAL_SELF_TERM);
		break;

	case SIGINT:
#ifdef SIGQUIT
	case SIGQUIT:
#endif
		if (main_config.debug_memory || main_config.memory_report) {
			radius_signal_self(RADIUS_SIGNAL_SELF_TERM);
			break;
		}
		/* FALL-THROUGH */

	default:
		fr_exit(sig);
	}
