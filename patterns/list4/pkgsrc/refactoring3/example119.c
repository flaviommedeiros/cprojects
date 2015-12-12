switch(t->type) {
	  case TCOM:
		rv = comexec(t, tp, ap, flags);
		break;

	  case TPAREN:
		rv = execute(t->left, flags|XFORK);
		break;

	  case TPIPE:
		flags |= XFORK;
		flags &= ~XEXEC;
		e->savefd[0] = savefd(0, 0);
		(void) ksh_dup2(e->savefd[0], 0, FALSE); /* stdin of first */
		e->savefd[1] = savefd(1, 0);
		while (t->type == TPIPE) {
			openpipe(pv);
			(void) ksh_dup2(pv[1], 1, FALSE); /* stdout of curr */
			/* Let exchild() close pv[0] in child
			 * (if this isn't done, commands like
			 *    (: ; cat /etc/termcap) | sleep 1
			 *  will hang forever).
			 */
			exchild(t->left, flags|XPIPEO|XCCLOSE, pv[0]);
			(void) ksh_dup2(pv[0], 0, FALSE); /* stdin of next */
			closepipe(pv);
			flags |= XPIPEI;
			t = t->right;
		}
		restfd(1, e->savefd[1]); /* stdout of last */
		e->savefd[1] = 0; /* no need to re-restore this */
		/* Let exchild() close 0 in parent, after fork, before wait */
		i = exchild(t, flags|XPCLOSE, 0);
		if (!(flags&XBGND) && !(flags&XXCOM))
			rv = i;
		break;

	  case TLIST:
		while (t->type == TLIST) {
			execute(t->left, flags & XERROK);
			t = t->right;
		}
		rv = execute(t, flags & XERROK);
		break;

#ifdef KSH
	  case TCOPROC:
	  {
# ifdef JOB_SIGS
		sigset_t	omask;
# endif /* JOB_SIGS */

# ifdef JOB_SIGS
		/* Block sigchild as we are using things changed in the
		 * signal handler
		 */
		sigprocmask(SIG_BLOCK, &sm_sigchld, &omask);
		e->type = E_ERRH;
		i = ksh_sigsetjmp(e->jbuf, 0);
		if (i) {
			sigprocmask(SIG_SETMASK, &omask, (sigset_t *) 0);
			quitenv();
			unwind(i);
			/*NOTREACHED*/
		}
# endif /* JOB_SIGS */
		/* Already have a (live) co-process? */
		if (coproc.job && coproc.write >= 0)
			errorf("coprocess already exists");

		/* Can we re-use the existing co-process pipe? */
		coproc_cleanup(TRUE);

		/* do this before opening pipes, in case these fail */
		e->savefd[0] = savefd(0, 0);
		e->savefd[1] = savefd(1, 0);

		openpipe(pv);
		if (pv[0] != 0) {
			ksh_dup2(pv[0], 0, FALSE);
			close(pv[0]);
		}
		coproc.write = pv[1];
		coproc.job = (void *) 0;

		if (coproc.readw >= 0)
			ksh_dup2(coproc.readw, 1, FALSE);
		else {
			openpipe(pv);
			coproc.read = pv[0];
			ksh_dup2(pv[1], 1, FALSE);
			coproc.readw = pv[1];	 /* closed before first read */
			coproc.njobs = 0;
			/* create new coprocess id */
			++coproc.id;
		}
# ifdef JOB_SIGS
		sigprocmask(SIG_SETMASK, &omask, (sigset_t *) 0);
		e->type = E_EXEC; /* no more need for error handler */
# endif /* JOB_SIGS */

		/* exchild() closes coproc.* in child after fork,
		 * will also increment coproc.njobs when the
		 * job is actually created.
		 */
		flags &= ~XEXEC;
		exchild(t->left, flags|XBGND|XFORK|XCOPROC|XCCLOSE,
			coproc.readw);
		break;
	  }
#endif /* KSH */

	  case TASYNC:
		/* XXX non-optimal, I think - "(foo &)", forks for (),
		 * forks again for async...  parent should optimize
		 * this to "foo &"...
		 */
		rv = execute(t->left, (flags&~XEXEC)|XBGND|XFORK);
		break;

	  case TOR:
	  case TAND:
		rv = execute(t->left, XERROK);
		if (t->right != NULL && (rv == 0) == (t->type == TAND))
			rv = execute(t->right, flags & XERROK);
		else
			flags |= XERROK;
		break;

	  case TBANG:
		rv = !execute(t->right, XERROK);
		break;

#ifdef KSH
	  case TDBRACKET:
	    {
		Test_env te;

		te.flags = TEF_DBRACKET;
		te.pos.wp = t->args;
		te.isa = dbteste_isa;
		te.getopnd = dbteste_getopnd;
		te.eval = dbteste_eval;
		te.error = dbteste_error;

		rv = test_parse(&te);
		break;
	    }
#endif /* KSH */

	  case TFOR:
#ifdef KSH
	  case TSELECT:
	    {
		volatile bool_t is_first = TRUE;
#endif /* KSH */
		ap = (t->vars != NULL) ?
			  eval(t->vars, DOBLANK|DOGLOB|DOTILDE)
			: e->loc->argv + 1;
		e->type = E_LOOP;
		while (1) {
			i = ksh_sigsetjmp(e->jbuf, 0);
			if (!i)
				break;
			if ((e->flags&EF_BRKCONT_PASS)
			    || (i != LBREAK && i != LCONTIN))
			{
				quitenv();
				unwind(i);
			} else if (i == LBREAK) {
				rv = 0;
				goto Break;
			}
		}
		rv = 0; /* in case of a continue */
		if (t->type == TFOR) {
			while (*ap != NULL) {
				setstr(global(t->str), *ap++, KSH_UNWIND_ERROR);
				rv = execute(t->left, flags & XERROK);
			}
		}
#ifdef KSH
		else { /* TSELECT */
			for (;;) {
				if (!(cp = do_selectargs(ap, is_first))) {
					rv = 1;
					break;
				}
				is_first = FALSE;
				setstr(global(t->str), cp, KSH_UNWIND_ERROR);
				rv = execute(t->left, flags & XERROK);
			}
		}
	    }
#endif /* KSH */
		break;

	  case TWHILE:
	  case TUNTIL:
		e->type = E_LOOP;
		while (1) {
			i = ksh_sigsetjmp(e->jbuf, 0);
			if (!i)
				break;
			if ((e->flags&EF_BRKCONT_PASS)
			    || (i != LBREAK && i != LCONTIN))
			{
				quitenv();
				unwind(i);
			} else if (i == LBREAK) {
				rv = 0;
				goto Break;
			}
		}
		rv = 0; /* in case of a continue */
		while ((execute(t->left, XERROK) == 0) == (t->type == TWHILE))
			rv = execute(t->right, flags & XERROK);
		break;

	  case TIF:
	  case TELIF:
		if (t->right == NULL)
			break;	/* should be error */
		rv = execute(t->left, XERROK) == 0 ?
			execute(t->right->left, flags & XERROK) :
			execute(t->right->right, flags & XERROK);
		break;

	  case TCASE:
		cp = evalstr(t->str, DOTILDE);
		for (t = t->left; t != NULL && t->type == TPAT; t = t->right)
		    for (ap = t->vars; *ap; ap++)
			if ((s = evalstr(*ap, DOTILDE|DOPAT))
			    && gmatch(cp, s, FALSE))
				goto Found;
		break;
	  Found:
		rv = execute(t->left, flags & XERROK);
		break;

	  case TBRACE:
		rv = execute(t->left, flags & XERROK);
		break;

	  case TFUNCT:
		rv = define(t->str, t);
		break;

	  case TTIME:
		/* Clear XEXEC so nested execute() call doesn't exit
		 * (allows "ls -l | time grep foo").
		 */
		rv = timex(t, flags & ~XEXEC);
		break;

	  case TEXEC:		/* an eval'd TCOM */
		s = t->args[0];
		ap = makenv();
#ifndef F_SETFD
		for (i = 0; i < sizeof(clexec_tab); i++)
			if (clexec_tab[i]) {
				close(i);
				clexec_tab[i] = 0;
			}
#endif
		restoresigs();
		cleanup_proc_env();
		/* XINTACT bit is for OS2 */
		ksh_execve(t->str, t->args, ap, (flags & XINTACT) ? 1 : 0);
		if (errno == ENOEXEC)
			scriptexec(t, ap);
		else
			errorf("%s: %s", s, strerror(errno));
	}
