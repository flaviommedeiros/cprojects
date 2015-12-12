static const char *lib_features[] = {
#if !defined(NDEBUG)	/* libc assert.h stuff */
	"assert",
#endif
	"debug",	/* always enabled */
	NULL
};
