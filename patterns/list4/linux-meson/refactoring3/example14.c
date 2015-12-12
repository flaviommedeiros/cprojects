switch (mode) {
	case SECCOMP_MODE_STRICT:
		syscall = mode1_syscalls;
#ifdef CONFIG_COMPAT
		if (is_compat_task())
			syscall = mode1_syscalls_32;
#endif
		do {
			if (*syscall == this_syscall)
				return 0;
		} while (*++syscall);
		exit_sig = SIGKILL;
		ret = SECCOMP_RET_KILL;
		break;
#ifdef CONFIG_SECCOMP_FILTER
	case SECCOMP_MODE_FILTER: {
		int data;
		struct pt_regs *regs = task_pt_regs(current);
		ret = seccomp_run_filters(this_syscall);
		data = ret & SECCOMP_RET_DATA;
		ret &= SECCOMP_RET_ACTION;
		switch (ret) {
		case SECCOMP_RET_ERRNO:
			/* Set the low-order 16-bits as a errno. */
			syscall_set_return_value(current, regs,
						 -data, 0);
			goto skip;
		case SECCOMP_RET_TRAP:
			/* Show the handler the original registers. */
			syscall_rollback(current, regs);
			/* Let the filter pass back 16 bits of data. */
			seccomp_send_sigsys(this_syscall, data);
			goto skip;
		case SECCOMP_RET_TRACE:
			/* Skip these calls if there is no tracer. */
			if (!ptrace_event_enabled(current, PTRACE_EVENT_SECCOMP)) {
				syscall_set_return_value(current, regs,
							 -ENOSYS, 0);
				goto skip;
			}
			/* Allow the BPF to provide the event message */
			ptrace_event(PTRACE_EVENT_SECCOMP, data);
			/*
			 * The delivery of a fatal signal during event
			 * notification may silently skip tracer notification.
			 * Terminating the task now avoids executing a system
			 * call that may not be intended.
			 */
			if (fatal_signal_pending(current))
				break;
			if (syscall_get_nr(current, regs) < 0)
				goto skip;  /* Explicit request to skip. */

			return 0;
		case SECCOMP_RET_ALLOW:
			return 0;
		case SECCOMP_RET_KILL:
		default:
			break;
		}
		exit_sig = SIGSYS;
		break;
	}
#endif
	default:
		BUG();
	}
