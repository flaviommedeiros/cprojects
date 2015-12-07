#ifdef S_ISSOCK
if (S_ISSOCK(mode)) {
		return "socket";
	} else
#endif
	return "";
