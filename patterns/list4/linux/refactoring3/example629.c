switch (request) {
		case PTRACE_PEEKUSR:
			ret = compat_ptrace_read_user(child, addr, datap);
			break;

		case PTRACE_POKEUSR:
			ret = compat_ptrace_write_user(child, addr, data);
			break;

		case COMPAT_PTRACE_GETREGS:
			ret = copy_regset_to_user(child,
						  &user_aarch32_view,
						  REGSET_COMPAT_GPR,
						  0, sizeof(compat_elf_gregset_t),
						  datap);
			break;

		case COMPAT_PTRACE_SETREGS:
			ret = copy_regset_from_user(child,
						    &user_aarch32_view,
						    REGSET_COMPAT_GPR,
						    0, sizeof(compat_elf_gregset_t),
						    datap);
			break;

		case COMPAT_PTRACE_GET_THREAD_AREA:
			ret = put_user((compat_ulong_t)child->thread.tp_value,
				       (compat_ulong_t __user *)datap);
			break;

		case COMPAT_PTRACE_SET_SYSCALL:
			task_pt_regs(child)->syscallno = data;
			ret = 0;
			break;

		case COMPAT_PTRACE_GETVFPREGS:
			ret = copy_regset_to_user(child,
						  &user_aarch32_view,
						  REGSET_COMPAT_VFP,
						  0, VFP_STATE_SIZE,
						  datap);
			break;

		case COMPAT_PTRACE_SETVFPREGS:
			ret = copy_regset_from_user(child,
						    &user_aarch32_view,
						    REGSET_COMPAT_VFP,
						    0, VFP_STATE_SIZE,
						    datap);
			break;

#ifdef CONFIG_HAVE_HW_BREAKPOINT
		case COMPAT_PTRACE_GETHBPREGS:
			ret = compat_ptrace_gethbpregs(child, addr, datap);
			break;

		case COMPAT_PTRACE_SETHBPREGS:
			ret = compat_ptrace_sethbpregs(child, addr, datap);
			break;
#endif

		default:
			ret = compat_ptrace_request(child, request, addr,
						    data);
			break;
	}
