switch (*arg) {
#ifdef SMFCONV
	case 'r':
		opt_rcpcv_dll = 1;
		return 0:
	case 'R':
		opt_rcpcv_dll = 0;
		return 0;
#else
	case 'r':
	case 'R':
		ctl->cmsg(CMSG_ERROR, VERB_NORMAL,
				"-w%c option is not supported", *arg);
		return 1;
#endif	/* SMFCONV */
	default:
		ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "-w: Illegal mode `%c'", *arg);
		return 1;
	}
