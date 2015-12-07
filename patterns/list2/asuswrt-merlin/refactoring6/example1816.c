if (
#ifndef linux
	 getuid() == geteuid() && getgid() == getegid() &&
#endif
	 iflag
	) {
		shinit = lookupvar("ENV");
		if (shinit != NULL && *shinit != '\0') {
			read_profile(shinit);
		}
	}
