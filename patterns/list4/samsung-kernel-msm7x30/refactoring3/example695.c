switch (request) {
	/* read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR: {
		unsigned long tmp;

		ret = -EIO;
		if ((addr & (sizeof(data) - 1)) || addr >= sizeof(struct user))
			break;

		tmp = 0;  /* Default return condition */
		if (addr < sizeof(struct user_regs_struct))
			tmp = getreg(child, addr);
		else if (addr >= offsetof(struct user, u_debugreg[0]) &&
			 addr <= offsetof(struct user, u_debugreg[7])) {
			addr -= offsetof(struct user, u_debugreg[0]);
			tmp = ptrace_get_debugreg(child, addr / sizeof(data));
		}
		ret = put_user(tmp, datap);
		break;
	}

	case PTRACE_POKEUSR: /* write the word at location addr in the USER area */
		ret = -EIO;
		if ((addr & (sizeof(data) - 1)) || addr >= sizeof(struct user))
			break;

		if (addr < sizeof(struct user_regs_struct))
			ret = putreg(child, addr, data);
		else if (addr >= offsetof(struct user, u_debugreg[0]) &&
			 addr <= offsetof(struct user, u_debugreg[7])) {
			addr -= offsetof(struct user, u_debugreg[0]);
			ret = ptrace_set_debugreg(child,
						  addr / sizeof(data), data);
		}
		break;

	case PTRACE_GETREGS:	/* Get all gp regs from the child. */
		return copy_regset_to_user(child,
					   task_user_regset_view(current),
					   REGSET_GENERAL,
					   0, sizeof(struct user_regs_struct),
					   datap);

	case PTRACE_SETREGS:	/* Set all gp regs in the child. */
		return copy_regset_from_user(child,
					     task_user_regset_view(current),
					     REGSET_GENERAL,
					     0, sizeof(struct user_regs_struct),
					     datap);

	case PTRACE_GETFPREGS:	/* Get the child FPU state. */
		return copy_regset_to_user(child,
					   task_user_regset_view(current),
					   REGSET_FP,
					   0, sizeof(struct user_i387_struct),
					   datap);

	case PTRACE_SETFPREGS:	/* Set the child FPU state. */
		return copy_regset_from_user(child,
					     task_user_regset_view(current),
					     REGSET_FP,
					     0, sizeof(struct user_i387_struct),
					     datap);

#ifdef CONFIG_X86_32
	case PTRACE_GETFPXREGS:	/* Get the child extended FPU state. */
		return copy_regset_to_user(child, &user_x86_32_view,
					   REGSET_XFP,
					   0, sizeof(struct user_fxsr_struct),
					   datap) ? -EIO : 0;

	case PTRACE_SETFPXREGS:	/* Set the child extended FPU state. */
		return copy_regset_from_user(child, &user_x86_32_view,
					     REGSET_XFP,
					     0, sizeof(struct user_fxsr_struct),
					     datap) ? -EIO : 0;
#endif

#if defined CONFIG_X86_32 || defined CONFIG_IA32_EMULATION
	case PTRACE_GET_THREAD_AREA:
		if ((int) addr < 0)
			return -EIO;
		ret = do_get_thread_area(child, addr,
					(struct user_desc __user *)data);
		break;

	case PTRACE_SET_THREAD_AREA:
		if ((int) addr < 0)
			return -EIO;
		ret = do_set_thread_area(child, addr,
					(struct user_desc __user *)data, 0);
		break;
#endif

#ifdef CONFIG_X86_64
		/* normal 64bit interface to access TLS data.
		   Works just like arch_prctl, except that the arguments
		   are reversed. */
	case PTRACE_ARCH_PRCTL:
		ret = do_arch_prctl(child, data, addr);
		break;
#endif

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
