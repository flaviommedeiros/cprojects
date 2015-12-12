switch (special(vp->name)) {
	  case V_PATH:
		if (path)
			afree(path, APERM);
		path = str_save(str_val(vp), APERM);
		flushcom(1);	/* clear tracked aliases */
		break;
	  case V_IFS:
		setctypes(s = str_val(vp), C_IFS);
		ifs0 = *s;
		break;
	  case V_OPTIND:
		vp->flag &= ~SPECIAL;
		getopts_reset((int) intval(vp));
		vp->flag |= SPECIAL;
		break;
	  case V_POSIXLY_CORRECT:
		change_flag(FPOSIX, OF_SPECIAL, 1);
		break;
	  case V_TMPDIR:
		if (tmpdir) {
			afree(tmpdir, APERM);
			tmpdir = (char *) 0;
		}
		/* Use tmpdir iff it is an absolute path, is writable and
		 * searchable and is a directory...
		 */
		{
			struct stat statb;
			s = str_val(vp);
			if (ISABSPATH(s) && eaccess(s, W_OK|X_OK) == 0
			    && stat(s, &statb) == 0 && S_ISDIR(statb.st_mode))
				tmpdir = str_save(s, APERM);
		}
		break;
#ifdef HISTORY
	  case V_HISTSIZE:
		vp->flag &= ~SPECIAL;
		sethistsize((int) intval(vp));
		vp->flag |= SPECIAL;
		break;
	  case V_HISTFILE:
		sethistfile(str_val(vp));
		break;
#endif /* HISTORY */
#ifdef EDIT
	  case V_VISUAL:
		set_editmode(str_val(vp));
		break;
	  case V_EDITOR:
		if (!(global("VISUAL")->flag & ISSET))
			set_editmode(str_val(vp));
		break;
	  case V_COLUMNS:
		if ((x_cols = intval(vp)) <= MIN_COLS)
			x_cols = MIN_COLS;
		break;
#endif /* EDIT */
#ifdef KSH
	  case V_MAIL:
		mbset(str_val(vp));
		break;
	  case V_MAILPATH:
		mpset(str_val(vp));
		break;
	  case V_MAILCHECK:
		vp->flag &= ~SPECIAL;
		mcset(intval(vp));
		vp->flag |= SPECIAL;
		break;
	  case V_RANDOM:
		vp->flag &= ~SPECIAL;
		srand((unsigned int)intval(vp));
		vp->flag |= SPECIAL;
		break;
	  case V_SECONDS:
		vp->flag &= ~SPECIAL;
		seconds = time((time_t*) 0) - intval(vp);
		vp->flag |= SPECIAL;
		break;
	  case V_TMOUT:
		/* at&t ksh seems to do this (only listen if integer) */
		if (vp->flag & INTEGER)
			ksh_tmout = vp->val.i >= 0 ? vp->val.i : 0;
		break;
#endif /* KSH */
	  case V_LINENO:
		vp->flag &= ~SPECIAL;
		/* The -1 is because line numbering starts at 1. */
		user_lineno = (unsigned int) intval(vp) - current_lineno - 1;
		vp->flag |= SPECIAL;
		break;
	}
