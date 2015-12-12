switch (uc->cmd) {
	case 0: return;

#ifdef SYM_LINUX_DEBUG_CONTROL_SUPPORT
	case UC_SETDEBUG:
		sym_debug_flags = uc->data;
		break;
#endif
	case UC_SETVERBOSE:
		np->verbose = uc->data;
		break;
	default:
		/*
		 * We assume that other commands apply to targets.
		 * This should always be the case and avoid the below 
		 * 4 lines to be repeated 6 times.
		 */
		for (t = 0; t < SYM_CONF_MAX_TARGET; t++) {
			if (!((uc->target >> t) & 1))
				continue;
			tp = &np->target[t];
			if (!tp->nlcb)
				continue;

			switch (uc->cmd) {

			case UC_SETSYNC:
				if (!uc->data || uc->data >= 255) {
					tp->tgoal.iu = tp->tgoal.dt =
						tp->tgoal.qas = 0;
					tp->tgoal.offset = 0;
				} else if (uc->data <= 9 && np->minsync_dt) {
					if (uc->data < np->minsync_dt)
						uc->data = np->minsync_dt;
					tp->tgoal.iu = tp->tgoal.dt =
						tp->tgoal.qas = 1;
					tp->tgoal.width = 1;
					tp->tgoal.period = uc->data;
					tp->tgoal.offset = np->maxoffs_dt;
				} else {
					if (uc->data < np->minsync)
						uc->data = np->minsync;
					tp->tgoal.iu = tp->tgoal.dt =
						tp->tgoal.qas = 0;
					tp->tgoal.period = uc->data;
					tp->tgoal.offset = np->maxoffs;
				}
				tp->tgoal.check_nego = 1;
				break;
			case UC_SETWIDE:
				tp->tgoal.width = uc->data ? 1 : 0;
				tp->tgoal.check_nego = 1;
				break;
			case UC_SETTAGS:
				for (l = 0; l < SYM_CONF_MAX_LUN; l++)
					sym_tune_dev_queuing(tp, l, uc->data);
				break;
			case UC_RESETDEV:
				tp->to_reset = 1;
				np->istat_sem = SEM;
				OUTB(np, nc_istat, SIGP|SEM);
				break;
			case UC_CLEARDEV:
				for (l = 0; l < SYM_CONF_MAX_LUN; l++) {
					struct sym_lcb *lp = sym_lp(tp, l);
					if (lp) lp->to_clear = 1;
				}
				np->istat_sem = SEM;
				OUTB(np, nc_istat, SIGP|SEM);
				break;
			case UC_SETFLAG:
				tp->usrflags = uc->data;
				break;
			}
		}
		break;
	}
