switch (request) {
	/* read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR: {
		unsigned long tmp;

		ret = -EIO;
		if ((addr & 3) || addr < 0 ||
		    addr > sizeof(struct user) - 3)
			break;

		if (addr < sizeof(struct pt_regs))
			tmp = get_stack_long(child, addr);
		else if (addr >= offsetof(struct user, fpu) &&
			 addr < offsetof(struct user, u_fpvalid)) {
			if (!tsk_used_math(child)) {
				if (addr == offsetof(struct user, fpu.fpscr))
					tmp = FPSCR_INIT;
				else
					tmp = 0;
			} else {
				unsigned long index;
				ret = init_fpu(child);
				if (ret)
					break;
				index = addr - offsetof(struct user, fpu);
				tmp = ((unsigned long *)child->thread.xstate)
					[index >> 2];
			}
		} else if (addr == offsetof(struct user, u_fpvalid))
			tmp = !!tsk_used_math(child);
		else if (addr == PT_TEXT_ADDR)
			tmp = child->mm->start_code;
		else if (addr == PT_DATA_ADDR)
			tmp = child->mm->start_data;
		else if (addr == PT_TEXT_END_ADDR)
			tmp = child->mm->end_code;
		else if (addr == PT_TEXT_LEN)
			tmp = child->mm->end_code - child->mm->start_code;
		else
			tmp = 0;
		ret = put_user(tmp, datap);
		break;
	}

	case PTRACE_POKEUSR: /* write the word at location addr in the USER area */
		ret = -EIO;
		if ((addr & 3) || addr < 0 ||
		    addr > sizeof(struct user) - 3)
			break;

		if (addr < sizeof(struct pt_regs))
			ret = put_stack_long(child, addr, data);
		else if (addr >= offsetof(struct user, fpu) &&
			 addr < offsetof(struct user, u_fpvalid)) {
			unsigned long index;
			ret = init_fpu(child);
			if (ret)
				break;
			index = addr - offsetof(struct user, fpu);
			set_stopped_child_used_math(child);
			((unsigned long *)child->thread.xstate)
				[index >> 2] = data;
			ret = 0;
		} else if (addr == offsetof(struct user, u_fpvalid)) {
			conditional_stopped_child_used_math(data, child);
			ret = 0;
		}
		break;

	case PTRACE_GETREGS:
		return copy_regset_to_user(child, &user_sh_native_view,
					   REGSET_GENERAL,
					   0, sizeof(struct pt_regs),
					   datap);
	case PTRACE_SETREGS:
		return copy_regset_from_user(child, &user_sh_native_view,
					     REGSET_GENERAL,
					     0, sizeof(struct pt_regs),
					     datap);
#ifdef CONFIG_SH_FPU
	case PTRACE_GETFPREGS:
		return copy_regset_to_user(child, &user_sh_native_view,
					   REGSET_FPU,
					   0, sizeof(struct user_fpu_struct),
					   datap);
	case PTRACE_SETFPREGS:
		return copy_regset_from_user(child, &user_sh_native_view,
					     REGSET_FPU,
					     0, sizeof(struct user_fpu_struct),
					     datap);
#endif
#ifdef CONFIG_SH_DSP
	case PTRACE_GETDSPREGS:
		return copy_regset_to_user(child, &user_sh_native_view,
					   REGSET_DSP,
					   0, sizeof(struct pt_dspregs),
					   datap);
	case PTRACE_SETDSPREGS:
		return copy_regset_from_user(child, &user_sh_native_view,
					     REGSET_DSP,
					     0, sizeof(struct pt_dspregs),
					     datap);
#endif
	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
