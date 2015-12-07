#if USE_CONFIGPATH_LOGS
if (create_dirs)
#endif
	if (build_dir(fname)) {
		ERROR("failed to create dir for log file \"%s\" : %s", fname,
		      strerror(errno));
		return -1;
	}
