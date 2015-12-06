switch(*param) {
	case 's':
		opt_realquiet = true;
		break;
	case 'q':
		opt_quiet ^= true;
		break;
	case 'v':
		opt_log_output ^= true;
		if (opt_log_output)
			opt_quiet = false;
		break;
	case 'd':
		opt_debug ^= true;
		opt_log_output = opt_debug;
		if (opt_debug)
			opt_quiet = false;
		break;
	case 'r':
		opt_protocol ^= true;
		if (opt_protocol)
			opt_quiet = false;
		break;
	case 'p':
		want_per_device_stats ^= true;
		opt_log_output = want_per_device_stats;
		break;
	case 'n':
		opt_log_output = false;
		opt_debug = false;
		opt_quiet = false;
		opt_protocol = false;
		want_per_device_stats = false;
		opt_worktime = false;
		break;
	case 'w':
		opt_worktime ^= true;
		break;
#ifdef _MEMORY_DEBUG
	case 'y':
		cgmemspeedup();
		break;
	case 'z':
		cgmemrpt();
		break;
#endif
	default:
		// anything else just reports the settings
		break;
	}
