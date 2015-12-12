switch ((instr >> 1) & 0x3ff) {
		case 20:	/* lwarx */
			ea = xform_ea(instr, regs, 0);
			if (ea & 3)
				break;		/* can't handle misaligned */
			err = -EFAULT;
			if (!address_ok(regs, ea, 4))
				goto ldst_done;
			err = 0;
			__get_user_asmx(val, ea, err, "lwarx");
			if (!err)
				regs->gpr[rd] = val;
			goto ldst_done;

		case 150:	/* stwcx. */
			ea = xform_ea(instr, regs, 0);
			if (ea & 3)
				break;		/* can't handle misaligned */
			err = -EFAULT;
			if (!address_ok(regs, ea, 4))
				goto ldst_done;
			err = 0;
			__put_user_asmx(regs->gpr[rd], ea, err, "stwcx.", cr);
			if (!err)
				regs->ccr = (regs->ccr & 0x0fffffff) |
					(cr & 0xe0000000) |
					((regs->xer >> 3) & 0x10000000);
			goto ldst_done;

#ifdef __powerpc64__
		case 84:	/* ldarx */
			ea = xform_ea(instr, regs, 0);
			if (ea & 7)
				break;		/* can't handle misaligned */
			err = -EFAULT;
			if (!address_ok(regs, ea, 8))
				goto ldst_done;
			err = 0;
			__get_user_asmx(val, ea, err, "ldarx");
			if (!err)
				regs->gpr[rd] = val;
			goto ldst_done;

		case 214:	/* stdcx. */
			ea = xform_ea(instr, regs, 0);
			if (ea & 7)
				break;		/* can't handle misaligned */
			err = -EFAULT;
			if (!address_ok(regs, ea, 8))
				goto ldst_done;
			err = 0;
			__put_user_asmx(regs->gpr[rd], ea, err, "stdcx.", cr);
			if (!err)
				regs->ccr = (regs->ccr & 0x0fffffff) |
					(cr & 0xe0000000) |
					((regs->xer >> 3) & 0x10000000);
			goto ldst_done;

		case 21:	/* ldx */
		case 53:	/* ldux */
			err = read_mem(&regs->gpr[rd], xform_ea(instr, regs, u),
				       8, regs);
			goto ldst_done;
#endif

		case 23:	/* lwzx */
		case 55:	/* lwzux */
			err = read_mem(&regs->gpr[rd], xform_ea(instr, regs, u),
				       4, regs);
			goto ldst_done;

		case 87:	/* lbzx */
		case 119:	/* lbzux */
			err = read_mem(&regs->gpr[rd], xform_ea(instr, regs, u),
				       1, regs);
			goto ldst_done;

#ifdef CONFIG_ALTIVEC
		case 103:	/* lvx */
		case 359:	/* lvxl */
			if (!(regs->msr & MSR_VEC))
				break;
			ea = xform_ea(instr, regs, 0);
			err = do_vec_load(rd, do_lvx, ea, regs);
			goto ldst_done;

		case 231:	/* stvx */
		case 487:	/* stvxl */
			if (!(regs->msr & MSR_VEC))
				break;
			ea = xform_ea(instr, regs, 0);
			err = do_vec_store(rd, do_stvx, ea, regs);
			goto ldst_done;
#endif /* CONFIG_ALTIVEC */

#ifdef __powerpc64__
		case 149:	/* stdx */
		case 181:	/* stdux */
			val = regs->gpr[rd];
			err = write_mem(val, xform_ea(instr, regs, u), 8, regs);
			goto ldst_done;
#endif

		case 151:	/* stwx */
		case 183:	/* stwux */
			val = regs->gpr[rd];
			err = write_mem(val, xform_ea(instr, regs, u), 4, regs);
			goto ldst_done;

		case 215:	/* stbx */
		case 247:	/* stbux */
			val = regs->gpr[rd];
			err = write_mem(val, xform_ea(instr, regs, u), 1, regs);
			goto ldst_done;

		case 279:	/* lhzx */
		case 311:	/* lhzux */
			err = read_mem(&regs->gpr[rd], xform_ea(instr, regs, u),
				       2, regs);
			goto ldst_done;

#ifdef __powerpc64__
		case 341:	/* lwax */
		case 373:	/* lwaux */
			err = read_mem(&regs->gpr[rd], xform_ea(instr, regs, u),
				       4, regs);
			if (!err)
				regs->gpr[rd] = (signed int) regs->gpr[rd];
			goto ldst_done;
#endif

		case 343:	/* lhax */
		case 375:	/* lhaux */
			err = read_mem(&regs->gpr[rd], xform_ea(instr, regs, u),
				       2, regs);
			if (!err)
				regs->gpr[rd] = (signed short) regs->gpr[rd];
			goto ldst_done;

		case 407:	/* sthx */
		case 439:	/* sthux */
			val = regs->gpr[rd];
			err = write_mem(val, xform_ea(instr, regs, u), 2, regs);
			goto ldst_done;

#ifdef __powerpc64__
		case 532:	/* ldbrx */
			err = read_mem(&val, xform_ea(instr, regs, 0), 8, regs);
			if (!err)
				regs->gpr[rd] = byterev_8(val);
			goto ldst_done;

#endif

		case 534:	/* lwbrx */
			err = read_mem(&val, xform_ea(instr, regs, 0), 4, regs);
			if (!err)
				regs->gpr[rd] = byterev_4(val);
			goto ldst_done;

#ifdef CONFIG_PPC_FPU
		case 535:	/* lfsx */
		case 567:	/* lfsux */
			if (!(regs->msr & MSR_FP))
				break;
			ea = xform_ea(instr, regs, u);
			err = do_fp_load(rd, do_lfs, ea, 4, regs);
			goto ldst_done;

		case 599:	/* lfdx */
		case 631:	/* lfdux */
			if (!(regs->msr & MSR_FP))
				break;
			ea = xform_ea(instr, regs, u);
			err = do_fp_load(rd, do_lfd, ea, 8, regs);
			goto ldst_done;

		case 663:	/* stfsx */
		case 695:	/* stfsux */
			if (!(regs->msr & MSR_FP))
				break;
			ea = xform_ea(instr, regs, u);
			err = do_fp_store(rd, do_stfs, ea, 4, regs);
			goto ldst_done;

		case 727:	/* stfdx */
		case 759:	/* stfdux */
			if (!(regs->msr & MSR_FP))
				break;
			ea = xform_ea(instr, regs, u);
			err = do_fp_store(rd, do_stfd, ea, 8, regs);
			goto ldst_done;
#endif

#ifdef __powerpc64__
		case 660:	/* stdbrx */
			val = byterev_8(regs->gpr[rd]);
			err = write_mem(val, xform_ea(instr, regs, 0), 8, regs);
			goto ldst_done;

#endif
		case 662:	/* stwbrx */
			val = byterev_4(regs->gpr[rd]);
			err = write_mem(val, xform_ea(instr, regs, 0), 4, regs);
			goto ldst_done;

		case 790:	/* lhbrx */
			err = read_mem(&val, xform_ea(instr, regs, 0), 2, regs);
			if (!err)
				regs->gpr[rd] = byterev_2(val);
			goto ldst_done;

		case 918:	/* sthbrx */
			val = byterev_2(regs->gpr[rd]);
			err = write_mem(val, xform_ea(instr, regs, 0), 2, regs);
			goto ldst_done;

#ifdef CONFIG_VSX
		case 844:	/* lxvd2x */
		case 876:	/* lxvd2ux */
			if (!(regs->msr & MSR_VSX))
				break;
			rd |= (instr & 1) << 5;
			ea = xform_ea(instr, regs, u);
			err = do_vsx_load(rd, do_lxvd2x, ea, regs);
			goto ldst_done;

		case 972:	/* stxvd2x */
		case 1004:	/* stxvd2ux */
			if (!(regs->msr & MSR_VSX))
				break;
			rd |= (instr & 1) << 5;
			ea = xform_ea(instr, regs, u);
			err = do_vsx_store(rd, do_stxvd2x, ea, regs);
			goto ldst_done;

#endif /* CONFIG_VSX */
		}
