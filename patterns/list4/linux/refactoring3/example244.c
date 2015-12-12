switch (cmd) {
	case RAID_VERSION:
		err = get_version(argp);
		goto out;

#ifndef MODULE
	case RAID_AUTORUN:
		err = 0;
		autostart_arrays(arg);
		goto out;
#endif
	default:;
	}
