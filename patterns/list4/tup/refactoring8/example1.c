static const char *default_env[] = {
/* NOTE: Please increment PARSER_VERSION if these are modified */
	"PATH",
	"HOME",
#ifdef _WIN32
	/* Basic Windows variables */
	"SYSTEMROOT",
	/* Visual Studio variables */
	"DevEnvDir",
	"INCLUDE",
	"LIB",
	"LIBPATH",
	"TEMP",
	"TMP",
	"VCINSTALLDIR",
	"VS100COMNTOOLS",
	"VS90COMNTOOLS",
	"VSINSTALLDIR",
#endif
/* NOTE: Please increment PARSER_VERSION if these are modified */
};
