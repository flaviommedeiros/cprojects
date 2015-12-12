switch (request) {
	case PTRACE_PEEKTEXT:
	case PTRACE_PEEKDATA:
		return generic_ptrace_peekdata(child, addr, data);
	case PTRACE_POKETEXT:
	case PTRACE_POKEDATA:
		return generic_ptrace_pokedata(child, addr, data);

#ifdef PTRACE_OLDSETOPTIONS
	case PTRACE_OLDSETOPTIONS:
#endif
	case PTRACE_SETOPTIONS:
		ret = ptrace_setoptions(child, data);
		break;
	case PTRACE_GETEVENTMSG:
		ret = put_user(child->ptrace_message, datalp);
		break;

	case PTRACE_GETSIGINFO:
		ret = ptrace_getsiginfo(child, &siginfo);
		if (!ret)
			ret = copy_siginfo_to_user(datavp, &siginfo);
		break;

	case PTRACE_SETSIGINFO:
		if (copy_from_user(&siginfo, datavp, sizeof siginfo))
			ret = -EFAULT;
		else
			ret = ptrace_setsiginfo(child, &siginfo);
		break;

	case PTRACE_INTERRUPT:
		/*
		 * Stop tracee without any side-effect on signal or job
		 * control.  At least one trap is guaranteed to happen
		 * after this request.  If @child is already trapped, the
		 * current trap is not disturbed and another trap will
		 * happen after the current trap is ended with PTRACE_CONT.
		 *
		 * The actual trap might not be PTRACE_EVENT_STOP trap but
		 * the pending condition is cleared regardless.
		 */
		if (unlikely(!seized || !lock_task_sighand(child, &flags)))
			break;

		/*
		 * INTERRUPT doesn't disturb existing trap sans one
		 * exception.  If ptracer issued LISTEN for the current
		 * STOP, this INTERRUPT should clear LISTEN and re-trap
		 * tracee into STOP.
		 */
		if (likely(task_set_jobctl_pending(child, JOBCTL_TRAP_STOP)))
			ptrace_signal_wake_up(child, child->jobctl & JOBCTL_LISTENING);

		unlock_task_sighand(child, &flags);
		ret = 0;
		break;

	case PTRACE_LISTEN:
		/*
		 * Listen for events.  Tracee must be in STOP.  It's not
		 * resumed per-se but is not considered to be in TRACED by
		 * wait(2) or ptrace(2).  If an async event (e.g. group
		 * stop state change) happens, tracee will enter STOP trap
		 * again.  Alternatively, ptracer can issue INTERRUPT to
		 * finish listening and re-trap tracee into STOP.
		 */
		if (unlikely(!seized || !lock_task_sighand(child, &flags)))
			break;

		si = child->last_siginfo;
		if (likely(si && (si->si_code >> 8) == PTRACE_EVENT_STOP)) {
			child->jobctl |= JOBCTL_LISTENING;
			/*
			 * If NOTIFY is set, it means event happened between
			 * start of this trap and now.  Trigger re-trap.
			 */
			if (child->jobctl & JOBCTL_TRAP_NOTIFY)
				ptrace_signal_wake_up(child, true);
			ret = 0;
		}
		unlock_task_sighand(child, &flags);
		break;

	case PTRACE_DETACH:	 /* detach a process that was attached. */
		ret = ptrace_detach(child, data);
		break;

#ifdef CONFIG_BINFMT_ELF_FDPIC
	case PTRACE_GETFDPIC: {
		struct mm_struct *mm = get_task_mm(child);
		unsigned long tmp = 0;

		ret = -ESRCH;
		if (!mm)
			break;

		switch (addr) {
		case PTRACE_GETFDPIC_EXEC:
			tmp = mm->context.exec_fdpic_loadmap;
			break;
		case PTRACE_GETFDPIC_INTERP:
			tmp = mm->context.interp_fdpic_loadmap;
			break;
		default:
			break;
		}
		mmput(mm);

		ret = put_user(tmp, datalp);
		break;
	}
#endif

#ifdef PTRACE_SINGLESTEP
	case PTRACE_SINGLESTEP:
#endif
#ifdef PTRACE_SINGLEBLOCK
	case PTRACE_SINGLEBLOCK:
#endif
#ifdef PTRACE_SYSEMU
	case PTRACE_SYSEMU:
	case PTRACE_SYSEMU_SINGLESTEP:
#endif
	case PTRACE_SYSCALL:
	case PTRACE_CONT:
		return ptrace_resume(child, request, data);

	case PTRACE_KILL:
		if (child->exit_state)	/* already dead */
			return 0;
		return ptrace_resume(child, request, SIGKILL);

#ifdef CONFIG_HAVE_ARCH_TRACEHOOK
	case PTRACE_GETREGSET:
	case PTRACE_SETREGSET:
	{
		struct iovec kiov;
		struct iovec __user *uiov = datavp;

		if (!access_ok(VERIFY_WRITE, uiov, sizeof(*uiov)))
			return -EFAULT;

		if (__get_user(kiov.iov_base, &uiov->iov_base) ||
		    __get_user(kiov.iov_len, &uiov->iov_len))
			return -EFAULT;

		ret = ptrace_regset(child, request, addr, &kiov);
		if (!ret)
			ret = __put_user(kiov.iov_len, &uiov->iov_len);
		break;
	}
#endif
	default:
		break;
	}
