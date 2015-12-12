switch (special(vp->name)) {
	  case V_PATH:
		if (path)
			afree(path, APERM);
		path = str_save(def_path, APERM);
		flushcom(1);	/* clear tracked aliases */
		break;
	  case V_IFS:
		setctypes(" \t\n", C_IFS);
		ifs0 = ' ';
		break;
	  case V_TMPDIR:
		/* should not become unspecial */
		if (tmpdir) {
			afree(tmpdir, APERM);
			tmpdir = (char *) 0;
		}
		break;
#ifdef KSH
	  case V_MAIL:
		mbset((char *) 0);
		break;
	  case V_MAILPATH:
		mpset((char *) 0);
		break;
#endif /* KSH */

	  case V_LINENO:
#ifdef KSH
	  case V_MAILCHECK:	/* at&t ksh leaves previous value in place */
	  case V_RANDOM:
	  case V_SECONDS:
	  case V_TMOUT:		/* at&t ksh leaves previous value in place */
#endif /* KSH */
		unspecial(vp->name);
		break;

	  /* at&t ksh man page says OPTIND, OPTARG and _ lose special meaning,
	   * but OPTARG does not (still set by getopts) and _ is also still
	   * set in various places.
	   * Don't know what at&t does for:
	   *		MAIL, MAILPATH, HISTSIZE, HISTFILE,
	   * Unsetting these in at&t ksh does not loose the `specialness':
	   *    no effect: IFS, COLUMNS, PATH, TMPDIR,
	   *		VISUAL, EDITOR,
	   * pdkshisms: no effect:
	   *		POSIXLY_CORRECT (use set +o posix instead)
	   */
	}
