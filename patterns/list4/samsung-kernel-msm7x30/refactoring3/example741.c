switch (request) {
	/* read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR: {
		unsigned long tmp;

		ret = -EIO;
		if ((addr & 3) || addr < 0)
			break;

		if (addr < sizeof(struct pt_regs))
			tmp = get_stack_long(child, addr);
		else if ((addr >= offsetof(struct user, fpu)) &&
			 (addr <  offsetof(struct user, u_fpvalid))) {
			unsigned long index;
			ret = init_fpu(child);
			if (ret)
				break;
			index = addr - offsetof(struct user, fpu);
			tmp = get_fpu_long(child, index);
		} else if (addr == offsetof(struct user, u_fpvalid)) {
			tmp = !!tsk_used_math(child);
		} else {
			break;
		}
		ret = put_user(tmp, datap);
		break;
	}

	case PTRACE_POKEUSR:
                /* write the word at location addr in the USER area. We must
                   disallow any changes to certain SR bits or u_fpvalid, since
                   this could crash the kernel or result in a security
                   loophole. */
		ret = -EIO;
		if ((addr & 3) || addr < 0)
			break;

		if (addr < sizeof(struct pt_regs)) {
			/* Ignore change of top 32 bits of SR */
			if (addr == offsetof (struct pt_regs, sr)+4)
			{
				ret = 0;
				break;
			}
			/* If lower 32 bits of SR, ignore non-user bits */
			if (addr == offsetof (struct pt_regs, sr))
			{
				long cursr = get_stack_long(child, addr);
				data &= ~(SR_MASK);
				data |= (cursr & SR_MASK);
			}
			ret = put_stack_long(child, addr, data);
		}
		else if ((addr >= offsetof(struct user, fpu)) &&
			 (addr <  offsetof(struct user, u_fpvalid))) {
			unsigned long index;
			ret = init_fpu(child);
			if (ret)
				break;
			index = addr - offsetof(struct user, fpu);
			ret = put_fpu_long(child, index, data);
		}
		break;

	case PTRACE_GETREGS:
		return copy_regset_to_user(child, &user_sh64_native_view,
					   REGSET_GENERAL,
					   0, sizeof(struct pt_regs),
					   datap);
	case PTRACE_SETREGS:
		return copy_regset_from_user(child, &user_sh64_native_view,
					     REGSET_GENERAL,
					     0, sizeof(struct pt_regs),
					     datap);
#ifdef CONFIG_SH_FPU
	case PTRACE_GETFPREGS:
		return copy_regset_to_user(child, &user_sh64_native_view,
					   REGSET_FPU,
					   0, sizeof(struct user_fpu_struct),
					   datap);
	case PTRACE_SETFPREGS:
		return copy_regset_from_user(child, &user_sh64_native_view,
					     REGSET_FPU,
					     0, sizeof(struct user_fpu_struct),
					     datap);
#endif
	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
