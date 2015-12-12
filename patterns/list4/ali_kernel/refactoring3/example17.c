switch (request) {
	case PTRACE_PEEKTEXT:
	case PTRACE_PEEKDATA:
		ret = generic_ptrace_peekdata(child, addr, data);
		break;
	case PTRACE_POKETEXT:
	case PTRACE_POKEDATA:
		ret = generic_ptrace_pokedata(child, addr, data);
		break;

#ifdef PTRACE_OLDSETOPTIONS
	case PTRACE_OLDSETOPTIONS:
#endif
	case PTRACE_SETOPTIONS:
		ret = ptrace_set_options(child, engine, data);
		break;
	case PTRACE_GETEVENTMSG:
		ret = put_user(ptrace_context(engine)->eventmsg,
				(unsigned long __user *) data);
		break;

	case PTRACE_GETSIGINFO:
		ret = ptrace_rw_siginfo(child, ptrace_context(engine),
					&siginfo, false);
		if (!ret)
			ret = copy_siginfo_to_user((siginfo_t __user *) data,
						   &siginfo);
		break;

	case PTRACE_SETSIGINFO:
		if (copy_from_user(&siginfo, (siginfo_t __user *) data,
				   sizeof siginfo))
			ret = -EFAULT;
		else
			ret = ptrace_rw_siginfo(child, ptrace_context(engine),
						&siginfo, true);
		break;

	case PTRACE_DETACH:	 /* detach a process that was attached. */
		ret = ptrace_detach(child, data);
		break;

	case PTRACE_KILL:
		/* Ugly historical behaviour. */
		if (task_is_traced(child))
			ptrace_resume(child, engine, PTRACE_CONT, SIGKILL);
		ret = 0;
		break;

	case PTRACE_GETREGSET:
	case PTRACE_SETREGSET:
	{
		struct iovec kiov;
		struct iovec __user *uiov = (struct iovec __user *) data;

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

	default:
		ret = ptrace_resume(child, engine, request, data);
		break;
	}
