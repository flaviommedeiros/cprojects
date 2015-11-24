switch (sig) {
#ifdef HAVE_COLLECTDC_H
	case SIGPIPE:
	{
		struct timeval now;

		gettimeofday(&now, NULL);
		rs_collectd_reopen(list, &now);
	}
		break;
#endif

	case SIGINT:
	case SIGTERM:
	case SIGQUIT:
		DEBUG2("Signalling event loop to exit");
		fr_event_loop_exit(events, 1);
		break;

	default:
		ERROR("Unhandled signal %s", strsignal(sig));
		exit(EXIT_FAILURE);
	}
