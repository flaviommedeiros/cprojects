if (strchr(argv[0], '/') != NULL
#if ENABLE_FEATURE_SH_STANDALONE
	 || (applet_no = find_applet_by_name(argv[0])) >= 0
#endif
	) {
		tryexec(IF_FEATURE_SH_STANDALONE(applet_no,) argv[0], argv, envp);
		if (applet_no >= 0) {
			/* We tried execing ourself, but it didn't work.
			 * Maybe /proc/self/exe doesn't exist?
			 * Try $PATH search.
			 */
			goto try_PATH;
		}
		e = errno;
	} else {
 try_PATH:
		e = ENOENT;
		while ((cmdname = path_advance(&path, argv[0])) != NULL) {
			if (--idx < 0 && pathopt == NULL) {
				tryexec(IF_FEATURE_SH_STANDALONE(-1,) cmdname, argv, envp);
				if (errno != ENOENT && errno != ENOTDIR)
					e = errno;
			}
			stunalloc(cmdname);
		}
	}
