switch (opcode) {
	case 31:
		u = instr & UPDATE;
		op->ea = xform_ea(instr, regs);
		switch ((instr >> 1) & 0x3ff) {
		case 20:	/* lwarx */
			op->type = MKOP(LARX, 0, 4);
			break;

		case 150:	/* stwcx. */
			op->type = MKOP(STCX, 0, 4);
			break;

#ifdef __powerpc64__
		case 84:	/* ldarx */
			op->type = MKOP(LARX, 0, 8);
			break;

		case 214:	/* stdcx. */
			op->type = MKOP(STCX, 0, 8);
			break;

		case 21:	/* ldx */
		case 53:	/* ldux */
			op->type = MKOP(LOAD, u, 8);
			break;
#endif

		case 23:	/* lwzx */
		case 55:	/* lwzux */
			op->type = MKOP(LOAD, u, 4);
			break;

		case 87:	/* lbzx */
		case 119:	/* lbzux */
			op->type = MKOP(LOAD, u, 1);
			break;

#ifdef CONFIG_ALTIVEC
		case 103:	/* lvx */
		case 359:	/* lvxl */
			if (!(regs->msr & MSR_VEC))
				goto vecunavail;
			op->type = MKOP(LOAD_VMX, 0, 16);
			break;

		case 231:	/* stvx */
		case 487:	/* stvxl */
			if (!(regs->msr & MSR_VEC))
				goto vecunavail;
			op->type = MKOP(STORE_VMX, 0, 16);
			break;
#endif /* CONFIG_ALTIVEC */

#ifdef __powerpc64__
		case 149:	/* stdx */
		case 181:	/* stdux */
			op->type = MKOP(STORE, u, 8);
			break;
#endif

		case 151:	/* stwx */
		case 183:	/* stwux */
			op->type = MKOP(STORE, u, 4);
			break;

		case 215:	/* stbx */
		case 247:	/* stbux */
			op->type = MKOP(STORE, u, 1);
			break;

		case 279:	/* lhzx */
		case 311:	/* lhzux */
			op->type = MKOP(LOAD, u, 2);
			break;

#ifdef __powerpc64__
		case 341:	/* lwax */
		case 373:	/* lwaux */
			op->type = MKOP(LOAD, SIGNEXT | u, 4);
			break;
#endif

		case 343:	/* lhax */
		case 375:	/* lhaux */
			op->type = MKOP(LOAD, SIGNEXT | u, 2);
			break;

		case 407:	/* sthx */
		case 439:	/* sthux */
			op->type = MKOP(STORE, u, 2);
			break;

#ifdef __powerpc64__
		case 532:	/* ldbrx */
			op->type = MKOP(LOAD, BYTEREV, 8);
			break;

#endif
		case 533:	/* lswx */
			op->type = MKOP(LOAD_MULTI, 0, regs->xer & 0x7f);
			break;

		case 534:	/* lwbrx */
			op->type = MKOP(LOAD, BYTEREV, 4);
			break;

		case 597:	/* lswi */
			if (rb == 0)
				rb = 32;	/* # bytes to load */
			op->type = MKOP(LOAD_MULTI, 0, rb);
			op->ea = 0;
			if (ra)
				op->ea = truncate_if_32bit(regs->msr,
							   regs->gpr[ra]);
			break;

#ifdef CONFIG_PPC_FPU
		case 535:	/* lfsx */
		case 567:	/* lfsux */
			if (!(regs->msr & MSR_FP))
				goto fpunavail;
			op->type = MKOP(LOAD_FP, u, 4);
			break;

		case 599:	/* lfdx */
		case 631:	/* lfdux */
			if (!(regs->msr & MSR_FP))
				goto fpunavail;
			op->type = MKOP(LOAD_FP, u, 8);
			break;

		case 663:	/* stfsx */
		case 695:	/* stfsux */
			if (!(regs->msr & MSR_FP))
				goto fpunavail;
			op->type = MKOP(STORE_FP, u, 4);
			break;

		case 727:	/* stfdx */
		case 759:	/* stfdux */
			if (!(regs->msr & MSR_FP))
				goto fpunavail;
			op->type = MKOP(STORE_FP, u, 8);
			break;
#endif

#ifdef __powerpc64__
		case 660:	/* stdbrx */
			op->type = MKOP(STORE, BYTEREV, 8);
			op->val = byterev_8(regs->gpr[rd]);
			break;

#endif
		case 661:	/* stswx */
			op->type = MKOP(STORE_MULTI, 0, regs->xer & 0x7f);
			break;

		case 662:	/* stwbrx */
			op->type = MKOP(STORE, BYTEREV, 4);
			op->val = byterev_4(regs->gpr[rd]);
			break;

		case 725:
			if (rb == 0)
				rb = 32;	/* # bytes to store */
			op->type = MKOP(STORE_MULTI, 0, rb);
			op->ea = 0;
			if (ra)
				op->ea = truncate_if_32bit(regs->msr,
							   regs->gpr[ra]);
			break;

		case 790:	/* lhbrx */
			op->type = MKOP(LOAD, BYTEREV, 2);
			break;

		case 918:	/* sthbrx */
			op->type = MKOP(STORE, BYTEREV, 2);
			op->val = byterev_2(regs->gpr[rd]);
			break;

#ifdef CONFIG_VSX
		case 844:	/* lxvd2x */
		case 876:	/* lxvd2ux */
			if (!(regs->msr & MSR_VSX))
				goto vsxunavail;
			op->reg = rd | ((instr & 1) << 5);
			op->type = MKOP(LOAD_VSX, u, 16);
			break;

		case 972:	/* stxvd2x */
		case 1004:	/* stxvd2ux */
			if (!(regs->msr & MSR_VSX))
				goto vsxunavail;
			op->reg = rd | ((instr & 1) << 5);
			op->type = MKOP(STORE_VSX, u, 16);
			break;

#endif /* CONFIG_VSX */
		}
		break;

	case 32:	/* lwz */
	case 33:	/* lwzu */
		op->type = MKOP(LOAD, u, 4);
		op->ea = dform_ea(instr, regs);
		break;

	case 34:	/* lbz */
	case 35:	/* lbzu */
		op->type = MKOP(LOAD, u, 1);
		op->ea = dform_ea(instr, regs);
		break;

	case 36:	/* stw */
	case 37:	/* stwu */
		op->type = MKOP(STORE, u, 4);
		op->ea = dform_ea(instr, regs);
		break;

	case 38:	/* stb */
	case 39:	/* stbu */
		op->type = MKOP(STORE, u, 1);
		op->ea = dform_ea(instr, regs);
		break;

	case 40:	/* lhz */
	case 41:	/* lhzu */
		op->type = MKOP(LOAD, u, 2);
		op->ea = dform_ea(instr, regs);
		break;

	case 42:	/* lha */
	case 43:	/* lhau */
		op->type = MKOP(LOAD, SIGNEXT | u, 2);
		op->ea = dform_ea(instr, regs);
		break;

	case 44:	/* sth */
	case 45:	/* sthu */
		op->type = MKOP(STORE, u, 2);
		op->ea = dform_ea(instr, regs);
		break;

	case 46:	/* lmw */
		if (ra >= rd)
			break;		/* invalid form, ra in range to load */
		op->type = MKOP(LOAD_MULTI, 0, 4 * (32 - rd));
		op->ea = dform_ea(instr, regs);
		break;

	case 47:	/* stmw */
		op->type = MKOP(STORE_MULTI, 0, 4 * (32 - rd));
		op->ea = dform_ea(instr, regs);
		break;

#ifdef CONFIG_PPC_FPU
	case 48:	/* lfs */
	case 49:	/* lfsu */
		if (!(regs->msr & MSR_FP))
			goto fpunavail;
		op->type = MKOP(LOAD_FP, u, 4);
		op->ea = dform_ea(instr, regs);
		break;

	case 50:	/* lfd */
	case 51:	/* lfdu */
		if (!(regs->msr & MSR_FP))
			goto fpunavail;
		op->type = MKOP(LOAD_FP, u, 8);
		op->ea = dform_ea(instr, regs);
		break;

	case 52:	/* stfs */
	case 53:	/* stfsu */
		if (!(regs->msr & MSR_FP))
			goto fpunavail;
		op->type = MKOP(STORE_FP, u, 4);
		op->ea = dform_ea(instr, regs);
		break;

	case 54:	/* stfd */
	case 55:	/* stfdu */
		if (!(regs->msr & MSR_FP))
			goto fpunavail;
		op->type = MKOP(STORE_FP, u, 8);
		op->ea = dform_ea(instr, regs);
		break;
#endif

#ifdef __powerpc64__
	case 58:	/* ld[u], lwa */
		op->ea = dsform_ea(instr, regs);
		switch (instr & 3) {
		case 0:		/* ld */
			op->type = MKOP(LOAD, 0, 8);
			break;
		case 1:		/* ldu */
			op->type = MKOP(LOAD, UPDATE, 8);
			break;
		case 2:		/* lwa */
			op->type = MKOP(LOAD, SIGNEXT, 4);
			break;
		}
		break;

	case 62:	/* std[u] */
		op->ea = dsform_ea(instr, regs);
		switch (instr & 3) {
		case 0:		/* std */
			op->type = MKOP(STORE, 0, 8);
			break;
		case 1:		/* stdu */
			op->type = MKOP(STORE, UPDATE, 8);
			break;
		}
		break;
#endif /* __powerpc64__ */

	}
