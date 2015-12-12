switch (special(vp->name)) {
#ifdef KSH
	  case V_SECONDS:
		vp->flag &= ~SPECIAL;
		/* On start up the value of SECONDS is used before seconds
		 * has been set - don't do anything in this case
		 * (see initcoms[] in main.c).
		 */
		if (vp->flag & ISSET)
			setint(vp, (long) (time((time_t *)0) - seconds));
		vp->flag |= SPECIAL;
		break;
	  case V_RANDOM:
		vp->flag &= ~SPECIAL;
		setint(vp, (long) (rand() & 0x7fff));
		vp->flag |= SPECIAL;
		break;
#endif /* KSH */
#ifdef HISTORY
	  case V_HISTSIZE:
		vp->flag &= ~SPECIAL;
		setint(vp, (long) histsize);
		vp->flag |= SPECIAL;
		break;
#endif /* HISTORY */
	  case V_OPTIND:
		vp->flag &= ~SPECIAL;
		setint(vp, (long) user_opt.uoptind);
		vp->flag |= SPECIAL;
		break;
	  case V_LINENO:
		vp->flag &= ~SPECIAL;
		setint(vp, (long) current_lineno + user_lineno);
		vp->flag |= SPECIAL;
		break;
	}
