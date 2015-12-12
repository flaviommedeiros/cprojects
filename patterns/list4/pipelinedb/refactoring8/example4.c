char	   *output_files[] = {
	SERVER_LOG_FILE,
#ifdef WIN32
	/* unique file for pg_ctl start */
	SERVER_START_LOG_FILE,
#endif
	UTILITY_LOG_FILE,
	INTERNAL_LOG_FILE,
	NULL
};
