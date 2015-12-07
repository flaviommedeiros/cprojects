#ifdef S_ISLNK
if (S_ISLNK(mode)) {
		return "symbolic link";
	} else
#endif
#ifdef S_ISSOCK
	if (S_ISSOCK(mode)) {
		return "socket";
	} else
#endif
	return "";
