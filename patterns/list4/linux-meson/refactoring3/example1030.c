switch (opcode) {
	case 16:	/* bc */
		imm = (signed short)(instr & 0xfffc);
		if ((instr & 2) == 0)
			imm += regs->nip;
		regs->nip += 4;
		regs->nip = truncate_if_32bit(regs->msr, regs->nip);
		if (instr & 1)
			regs->link = regs->nip;
		if (branch_taken(instr, regs))
			regs->nip = imm;
		return 1;
#ifdef CONFIG_PPC64
	case 17:	/* sc */
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
#endif
	case 18:	/* b */
		imm = instr & 0x03fffffc;
		if (imm & 0x02000000)
			imm -= 0x04000000;
		if ((instr & 2) == 0)
			imm += regs->nip;
		if (instr & 1)
			regs->link = truncate_if_32bit(regs->msr, regs->nip + 4);
		imm = truncate_if_32bit(regs->msr, imm);
		regs->nip = imm;
		return 1;
	case 19:
		switch ((instr >> 1) & 0x3ff) {
		case 16:	/* bclr */
		case 528:	/* bcctr */
			imm = (instr & 0x400)? regs->ctr: regs->link;
			regs->nip = truncate_if_32bit(regs->msr, regs->nip + 4);
			imm = truncate_if_32bit(regs->msr, imm);
			if (instr & 1)
				regs->link = regs->nip;
			if (branch_taken(instr, regs))
				regs->nip = imm;
			return 1;

		case 18:	/* rfid, scary */
			return -1;

		case 150:	/* isync */
			isync();
			goto instr_done;

		case 33:	/* crnor */
		case 129:	/* crandc */
		case 193:	/* crxor */
		case 225:	/* crnand */
		case 257:	/* crand */
		case 289:	/* creqv */
		case 417:	/* crorc */
		case 449:	/* cror */
			ra = (instr >> 16) & 0x1f;
			rb = (instr >> 11) & 0x1f;
			rd = (instr >> 21) & 0x1f;
			ra = (regs->ccr >> (31 - ra)) & 1;
			rb = (regs->ccr >> (31 - rb)) & 1;
			val = (instr >> (6 + ra * 2 + rb)) & 1;
			regs->ccr = (regs->ccr & ~(1UL << (31 - rd))) |
				(val << (31 - rd));
			goto instr_done;
		}
		break;
	case 31:
		switch ((instr >> 1) & 0x3ff) {
		case 598:	/* sync */
#ifdef __powerpc64__
			switch ((instr >> 21) & 3) {
			case 1:		/* lwsync */
				asm volatile("lwsync" : : : "memory");
				goto instr_done;
			case 2:		/* ptesync */
				asm volatile("ptesync" : : : "memory");
				goto instr_done;
			}
#endif
			mb();
			goto instr_done;

		case 854:	/* eieio */
			eieio();
			goto instr_done;
		}
		break;
	}
