switch (request) {
	/* read the word at location addr in the USER area. */
	case PTRACE_PEEKUSR: {
		unsigned long index, tmp;

		ret = -EIO;
		/* convert to index and check */
#ifdef CONFIG_PPC32
		index = addr >> 2;
		if ((addr & 3) || (index > PT_FPSCR)
		    || (child->thread.regs == NULL))
#else
		index = addr >> 3;
		if ((addr & 7) || (index > PT_FPSCR))
#endif
			break;

		CHECK_FULL_REGS(child->thread.regs);
		if (index < PT_FPR0) {
			ret = ptrace_get_reg(child, (int) index, &tmp);
			if (ret)
				break;
		} else {
			unsigned int fpidx = index - PT_FPR0;

			flush_fp_to_thread(child);
			if (fpidx < (PT_FPSCR - PT_FPR0))
				memcpy(&tmp, &child->thread.TS_FPR(fpidx),
				       sizeof(long));
			else
				tmp = child->thread.fp_state.fpscr;
		}
		ret = put_user(tmp, datalp);
		break;
	}

	/* write the word at location addr in the USER area */
	case PTRACE_POKEUSR: {
		unsigned long index;

		ret = -EIO;
		/* convert to index and check */
#ifdef CONFIG_PPC32
		index = addr >> 2;
		if ((addr & 3) || (index > PT_FPSCR)
		    || (child->thread.regs == NULL))
#else
		index = addr >> 3;
		if ((addr & 7) || (index > PT_FPSCR))
#endif
			break;

		CHECK_FULL_REGS(child->thread.regs);
		if (index < PT_FPR0) {
			ret = ptrace_put_reg(child, index, data);
		} else {
			unsigned int fpidx = index - PT_FPR0;

			flush_fp_to_thread(child);
			if (fpidx < (PT_FPSCR - PT_FPR0))
				memcpy(&child->thread.TS_FPR(fpidx), &data,
				       sizeof(long));
			else
				child->thread.fp_state.fpscr = data;
			ret = 0;
		}
		break;
	}

	case PPC_PTRACE_GETHWDBGINFO: {
		struct ppc_debug_info dbginfo;

		dbginfo.version = 1;
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
		dbginfo.num_instruction_bps = CONFIG_PPC_ADV_DEBUG_IACS;
		dbginfo.num_data_bps = CONFIG_PPC_ADV_DEBUG_DACS;
		dbginfo.num_condition_regs = CONFIG_PPC_ADV_DEBUG_DVCS;
		dbginfo.data_bp_alignment = 4;
		dbginfo.sizeof_condition = 4;
		dbginfo.features = PPC_DEBUG_FEATURE_INSN_BP_RANGE |
				   PPC_DEBUG_FEATURE_INSN_BP_MASK;
#ifdef CONFIG_PPC_ADV_DEBUG_DAC_RANGE
		dbginfo.features |=
				   PPC_DEBUG_FEATURE_DATA_BP_RANGE |
				   PPC_DEBUG_FEATURE_DATA_BP_MASK;
#endif
#else /* !CONFIG_PPC_ADV_DEBUG_REGS */
		dbginfo.num_instruction_bps = 0;
		dbginfo.num_data_bps = 1;
		dbginfo.num_condition_regs = 0;
#ifdef CONFIG_PPC64
		dbginfo.data_bp_alignment = 8;
#else
		dbginfo.data_bp_alignment = 4;
#endif
		dbginfo.sizeof_condition = 0;
#ifdef CONFIG_HAVE_HW_BREAKPOINT
		dbginfo.features = PPC_DEBUG_FEATURE_DATA_BP_RANGE;
		if (cpu_has_feature(CPU_FTR_DAWR))
			dbginfo.features |= PPC_DEBUG_FEATURE_DATA_BP_DAWR;
#else
		dbginfo.features = 0;
#endif /* CONFIG_HAVE_HW_BREAKPOINT */
#endif /* CONFIG_PPC_ADV_DEBUG_REGS */

		if (!access_ok(VERIFY_WRITE, datavp,
			       sizeof(struct ppc_debug_info)))
			return -EFAULT;
		ret = __copy_to_user(datavp, &dbginfo,
				     sizeof(struct ppc_debug_info)) ?
		      -EFAULT : 0;
		break;
	}

	case PPC_PTRACE_SETHWDEBUG: {
		struct ppc_hw_breakpoint bp_info;

		if (!access_ok(VERIFY_READ, datavp,
			       sizeof(struct ppc_hw_breakpoint)))
			return -EFAULT;
		ret = __copy_from_user(&bp_info, datavp,
				       sizeof(struct ppc_hw_breakpoint)) ?
		      -EFAULT : 0;
		if (!ret)
			ret = ppc_set_hwdebug(child, &bp_info);
		break;
	}

	case PPC_PTRACE_DELHWDEBUG: {
		ret = ppc_del_hwdebug(child, data);
		break;
	}

	case PTRACE_GET_DEBUGREG: {
#ifndef CONFIG_PPC_ADV_DEBUG_REGS
		unsigned long dabr_fake;
#endif
		ret = -EINVAL;
		/* We only support one DABR and no IABRS at the moment */
		if (addr > 0)
			break;
#ifdef CONFIG_PPC_ADV_DEBUG_REGS
		ret = put_user(child->thread.debug.dac1, datalp);
#else
		dabr_fake = ((child->thread.hw_brk.address & (~HW_BRK_TYPE_DABR)) |
			     (child->thread.hw_brk.type & HW_BRK_TYPE_DABR));
		ret = put_user(dabr_fake, datalp);
#endif
		break;
	}

	case PTRACE_SET_DEBUGREG:
		ret = ptrace_set_debugreg(child, addr, data);
		break;

#ifdef CONFIG_PPC64
	case PTRACE_GETREGS64:
#endif
	case PTRACE_GETREGS:	/* Get all pt_regs from the child. */
		return copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_GPR,
					   0, sizeof(struct pt_regs),
					   datavp);

#ifdef CONFIG_PPC64
	case PTRACE_SETREGS64:
#endif
	case PTRACE_SETREGS:	/* Set all gp regs in the child. */
		return copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_GPR,
					     0, sizeof(struct pt_regs),
					     datavp);

	case PTRACE_GETFPREGS: /* Get the child FPU state (FPR0...31 + FPSCR) */
		return copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_FPR,
					   0, sizeof(elf_fpregset_t),
					   datavp);

	case PTRACE_SETFPREGS: /* Set the child FPU state (FPR0...31 + FPSCR) */
		return copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_FPR,
					     0, sizeof(elf_fpregset_t),
					     datavp);

#ifdef CONFIG_ALTIVEC
	case PTRACE_GETVRREGS:
		return copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_VMX,
					   0, (33 * sizeof(vector128) +
					       sizeof(u32)),
					   datavp);

	case PTRACE_SETVRREGS:
		return copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_VMX,
					     0, (33 * sizeof(vector128) +
						 sizeof(u32)),
					     datavp);
#endif
#ifdef CONFIG_VSX
	case PTRACE_GETVSRREGS:
		return copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_VSX,
					   0, 32 * sizeof(double),
					   datavp);

	case PTRACE_SETVSRREGS:
		return copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_VSX,
					     0, 32 * sizeof(double),
					     datavp);
#endif
#ifdef CONFIG_SPE
	case PTRACE_GETEVRREGS:
		/* Get the child spe register state. */
		return copy_regset_to_user(child, &user_ppc_native_view,
					   REGSET_SPE, 0, 35 * sizeof(u32),
					   datavp);

	case PTRACE_SETEVRREGS:
		/* Set the child spe register state. */
		return copy_regset_from_user(child, &user_ppc_native_view,
					     REGSET_SPE, 0, 35 * sizeof(u32),
					     datavp);
#endif

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}
