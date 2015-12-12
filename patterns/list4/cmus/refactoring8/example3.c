const char * const op_pcm_options[] = {
	[CFG_SERVER_NAME] = "server_name",
#ifdef HAVE_SAMPLERATE
	[CFG_RESAMPLING_QUALITY] = "resampling_quality",
#endif
	NULL
};
