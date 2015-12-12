switch (opcode) {
	case 16:	/* bc */
		imm = (signed short)(instr & 0xfffc);
		if ((instr & 2) == 0)
			imm += regs->nip;
		regs->nip += 4;
		if ((regs->msr & MSR_SF) == 0)
			regs->nip &= 0xffffffffUL;
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
		regs->gpr[9] = regs->gpr[13];
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
		if (instr & 1) {
			regs->link = regs->nip + 4;
			if ((regs->msr & MSR_SF) == 0)
				regs->link &= 0xffffffffUL;
		}
		if ((regs->msr & MSR_SF) == 0)
			imm &= 0xffffffffUL;
		regs->nip = imm;
		return 1;
	case 19:
		switch (instr & 0x7fe) {
		case 0x20:	/* bclr */
		case 0x420:	/* bcctr */
			imm = (instr & 0x400)? regs->ctr: regs->link;
			regs->nip += 4;
			if ((regs->msr & MSR_SF) == 0) {
				regs->nip &= 0xffffffffUL;
				imm &= 0xffffffffUL;
			}
			if (instr & 1)
				regs->link = regs->nip;
			if (branch_taken(instr, regs))
				regs->nip = imm;
			return 1;
		case 0x24:	/* rfid, scary */
			return -1;
		}
	case 31:
		rd = (instr >> 21) & 0x1f;
		switch (instr & 0x7fe) {
		case 0xa6:	/* mfmsr */
			regs->gpr[rd] = regs->msr & MSR_MASK;
			regs->nip += 4;
			if ((regs->msr & MSR_SF) == 0)
				regs->nip &= 0xffffffffUL;
			return 1;
		case 0x124:	/* mtmsr */
			imm = regs->gpr[rd];
			if ((imm & MSR_RI) == 0)
				/* can't step mtmsr that would clear MSR_RI */
				return -1;
			regs->msr = imm;
			regs->nip += 4;
			return 1;
#ifdef CONFIG_PPC64
		case 0x164:	/* mtmsrd */
			/* only MSR_EE and MSR_RI get changed if bit 15 set */
			/* mtmsrd doesn't change MSR_HV and MSR_ME */
			imm = (instr & 0x10000)? 0x8002: 0xefffffffffffefffUL;
			imm = (regs->msr & MSR_MASK & ~imm)
				| (regs->gpr[rd] & imm);
			if ((imm & MSR_RI) == 0)
				/* can't step mtmsrd that would clear MSR_RI */
				return -1;
			regs->msr = imm;
			regs->nip += 4;
			if ((imm & MSR_SF) == 0)
				regs->nip &= 0xffffffffUL;
			return 1;
#endif
		case 0x26:	/* mfcr */
			regs->gpr[rd] = regs->ccr;
			regs->gpr[rd] &= 0xffffffffUL;
			goto mtspr_out;
		case 0x2a6:	/* mfspr */
			spr = (instr >> 11) & 0x3ff;
			switch (spr) {
			case 0x20:	/* mfxer */
				regs->gpr[rd] = regs->xer;
				regs->gpr[rd] &= 0xffffffffUL;
				goto mtspr_out;
			case 0x100:	/* mflr */
				regs->gpr[rd] = regs->link;
				goto mtspr_out;
			case 0x120:	/* mfctr */
				regs->gpr[rd] = regs->ctr;
				goto mtspr_out;
			}
			break;
		case 0x378:	/* orx */
			if (instr & 1)
				break;
			rs = (instr >> 21) & 0x1f;
			rb = (instr >> 11) & 0x1f;
			if (rs == rb) {		/* mr */
				rd = (instr >> 16) & 0x1f;
				regs->gpr[rd] = regs->gpr[rs];
				goto mtspr_out;
			}
			break;
		case 0x3a6:	/* mtspr */
			spr = (instr >> 11) & 0x3ff;
			switch (spr) {
			case 0x20:	/* mtxer */
				regs->xer = (regs->gpr[rd] & 0xffffffffUL);
				goto mtspr_out;
			case 0x100:	/* mtlr */
				regs->link = regs->gpr[rd];
				goto mtspr_out;
			case 0x120:	/* mtctr */
				regs->ctr = regs->gpr[rd];
mtspr_out:
				regs->nip += 4;
				return 1;
			}
		}
	}
