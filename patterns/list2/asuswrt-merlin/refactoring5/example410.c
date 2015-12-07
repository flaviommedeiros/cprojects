#ifdef REGISTRY_BACKEND
if (strequal(backend, "registry") || strequal(backend, "reg")) {
		err = smbconf_init_reg(mem_ctx, conf_ctx, path);
	} else
#endif
	if (strequal(backend, "file") || strequal(backend, "txt")) {
		err = smbconf_init_txt(mem_ctx, conf_ctx, path);
	} else if (sep == NULL) {
		/*
		 * If no separator was given in the source, and the string is
		 * not a known backend, assume file backend and use the source
		 * string as a path argument.
		 */
		err = smbconf_init_txt(mem_ctx, conf_ctx, backend);
	} else {
		/*
		 * Separator was specified but this is not a known backend.
		 * As a last resort, try to interpret the original source
		 * string as a file name that contains a ":" sign.
		 * This may occur with an include directive like this:
		 * 'include = /path/to/file.%T'
		 */
		err = smbconf_init_txt(mem_ctx, conf_ctx, source);
	}
