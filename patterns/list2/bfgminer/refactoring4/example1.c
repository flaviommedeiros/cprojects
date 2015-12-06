#ifdef UNIX_PATH_MAX
if (devpath_len >= UNIX_PATH_MAX)
#else
	if (devpath_len >= sizeof(sa.sun_path))
#endif
		return -1;
