#ifdef HAVE_GETCWD
if (LF_ISSET(DB_ARCH_ABS)) {
		/*
		 * XXX
		 * Can't trust getcwd(3) to set a valid errno, so don't display
		 * one unless we know it's good.  It's likely a permissions
		 * problem: use something bland and useless in the default
		 * return value, so we don't send somebody off in the wrong
		 * direction.
		 */
		__os_set_errno(0);
		if (getcwd(path, sizeof(path)) == NULL) {
			ret = __os_get_errno();
			__db_err(env,
			    ret, "no absolute path for the current directory");
			return (ret);
		}
		pref = path;
	} else
#endif
		pref = NULL;
