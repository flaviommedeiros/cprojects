switch (op.type & INSTR_TYPE_MASK) {
	case CACHEOP:
		if (!address_ok(regs, op.ea, 8))
			return 0;
		switch (op.type & CACHEOP_MASK) {
		case DCBST:
			__cacheop_user_asmx(op.ea, err, "dcbst");
			break;
		case DCBF:
			__cacheop_user_asmx(op.ea, err, "dcbf");
			break;
		case DCBTST:
			if (op.reg == 0)
				prefetchw((void *) op.ea);
			break;
		case DCBT:
			if (op.reg == 0)
				prefetch((void *) op.ea);
			break;
		case ICBI:
			__cacheop_user_asmx(op.ea, err, "icbi");
			break;
		}
		if (err)
			return 0;
		goto instr_done;

	case LARX:
		if (regs->msr & MSR_LE)
			return 0;
		if (op.ea & (size - 1))
			break;		/* can't handle misaligned */
		err = -EFAULT;
		if (!address_ok(regs, op.ea, size))
			goto ldst_done;
		err = 0;
		switch (size) {
		case 4:
			__get_user_asmx(val, op.ea, err, "lwarx");
			break;
		case 8:
			__get_user_asmx(val, op.ea, err, "ldarx");
			break;
		default:
			return 0;
		}
		if (!err)
			regs->gpr[op.reg] = val;
		goto ldst_done;

	case STCX:
		if (regs->msr & MSR_LE)
			return 0;
		if (op.ea & (size - 1))
			break;		/* can't handle misaligned */
		err = -EFAULT;
		if (!address_ok(regs, op.ea, size))
			goto ldst_done;
		err = 0;
		switch (size) {
		case 4:
			__put_user_asmx(op.val, op.ea, err, "stwcx.", cr);
			break;
		case 8:
			__put_user_asmx(op.val, op.ea, err, "stdcx.", cr);
			break;
		default:
			return 0;
		}
		if (!err)
			regs->ccr = (regs->ccr & 0x0fffffff) |
				(cr & 0xe0000000) |
				((regs->xer >> 3) & 0x10000000);
		goto ldst_done;

	case LOAD:
		if (regs->msr & MSR_LE)
			return 0;
		err = read_mem(&regs->gpr[op.reg], op.ea, size, regs);
		if (!err) {
			if (op.type & SIGNEXT)
				do_signext(&regs->gpr[op.reg], size);
			if (op.type & BYTEREV)
				do_byterev(&regs->gpr[op.reg], size);
		}
		goto ldst_done;

#ifdef CONFIG_PPC_FPU
	case LOAD_FP:
		if (regs->msr & MSR_LE)
			return 0;
		if (size == 4)
			err = do_fp_load(op.reg, do_lfs, op.ea, size, regs);
		else
			err = do_fp_load(op.reg, do_lfd, op.ea, size, regs);
		goto ldst_done;
#endif
#ifdef CONFIG_ALTIVEC
	case LOAD_VMX:
		if (regs->msr & MSR_LE)
			return 0;
		err = do_vec_load(op.reg, do_lvx, op.ea & ~0xfUL, regs);
		goto ldst_done;
#endif
#ifdef CONFIG_VSX
	case LOAD_VSX:
		if (regs->msr & MSR_LE)
			return 0;
		err = do_vsx_load(op.reg, do_lxvd2x, op.ea, regs);
		goto ldst_done;
#endif
	case LOAD_MULTI:
		if (regs->msr & MSR_LE)
			return 0;
		rd = op.reg;
		for (i = 0; i < size; i += 4) {
			nb = size - i;
			if (nb > 4)
				nb = 4;
			err = read_mem(&regs->gpr[rd], op.ea, nb, regs);
			if (err)
				return 0;
			if (nb < 4)	/* left-justify last bytes */
				regs->gpr[rd] <<= 32 - 8 * nb;
			op.ea += 4;
			++rd;
		}
		goto instr_done;

	case STORE:
		if (regs->msr & MSR_LE)
			return 0;
		if ((op.type & UPDATE) && size == sizeof(long) &&
		    op.reg == 1 && op.update_reg == 1 &&
		    !(regs->msr & MSR_PR) &&
		    op.ea >= regs->gpr[1] - STACK_INT_FRAME_SIZE) {
			err = handle_stack_update(op.ea, regs);
			goto ldst_done;
		}
		err = write_mem(op.val, op.ea, size, regs);
		goto ldst_done;

#ifdef CONFIG_PPC_FPU
	case STORE_FP:
		if (regs->msr & MSR_LE)
			return 0;
		if (size == 4)
			err = do_fp_store(op.reg, do_stfs, op.ea, size, regs);
		else
			err = do_fp_store(op.reg, do_stfd, op.ea, size, regs);
		goto ldst_done;
#endif
#ifdef CONFIG_ALTIVEC
	case STORE_VMX:
		if (regs->msr & MSR_LE)
			return 0;
		err = do_vec_store(op.reg, do_stvx, op.ea & ~0xfUL, regs);
		goto ldst_done;
#endif
#ifdef CONFIG_VSX
	case STORE_VSX:
		if (regs->msr & MSR_LE)
			return 0;
		err = do_vsx_store(op.reg, do_stxvd2x, op.ea, regs);
		goto ldst_done;
#endif
	case STORE_MULTI:
		if (regs->msr & MSR_LE)
			return 0;
		rd = op.reg;
		for (i = 0; i < size; i += 4) {
			val = regs->gpr[rd];
			nb = size - i;
			if (nb > 4)
				nb = 4;
			else
				val >>= 32 - 8 * nb;
			err = write_mem(val, op.ea, nb, regs);
			if (err)
				return 0;
			op.ea += 4;
			++rd;
		}
		goto instr_done;

	case MFMSR:
		regs->gpr[op.reg] = regs->msr & MSR_MASK;
		goto instr_done;

	case MTMSR:
		val = regs->gpr[op.reg];
		if ((val & MSR_RI) == 0)
			/* can't step mtmsr[d] that would clear MSR_RI */
			return -1;
		/* here op.val is the mask of bits to change */
		regs->msr = (regs->msr & ~op.val) | (val & op.val);
		goto instr_done;

#ifdef CONFIG_PPC64
	case SYSCALL:	/* sc */
		/*
		 * N.B. this uses knowledge about how the syscall
		 * entry code works.  If that is changed, this will
		 * need to be changed also.
		 */
		if (regs->gpr[0] == 0x1ebe &&
		    cpu_has_feature(CPU_FTR_REAL_LE)) {
			regs->msr ^= MSR_LE;
			goto instr_done;
		}
		regs->gpr[9] = regs->gpr[13];
		regs->gpr[10] = MSR_KERNEL;
		regs->gpr[11] = regs->nip + 4;
		regs->gpr[12] = regs->msr & MSR_MASK;
		regs->gpr[13] = (unsigned long) get_paca();
		regs->nip = (unsigned long) &system_call_common;
		regs->msr = MSR_KERNEL;
		return 1;

	case RFI:
		return -1;
#endif
	}
