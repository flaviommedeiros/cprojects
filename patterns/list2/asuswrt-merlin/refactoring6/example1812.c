if (strcmp(extension, "tgz" + 1) == 0
#if ENABLE_FEATURE_SEAMLESS_Z
	 || (extension[0] == 'Z' && extension[1] == '\0')
#endif
	) {
		extension[-1] = '\0';
	} else if (strcmp(extension, "tgz") == 0) {
		filename = xstrdup(filename);
		extension = strrchr(filename, '.');
		extension[2] = 'a';
		extension[3] = 'r';
	} else {
		return NULL;
	}
