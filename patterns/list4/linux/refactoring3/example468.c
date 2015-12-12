switch ((instr >> 1) & 0x3ff) {
		case 4:		/* tw */
			if (rd == 0x1f ||
			    (rd & trap_compare((int)regs->gpr[ra],
					       (int)regs->gpr[rb])))
				goto trap;
			goto instr_done;
#ifdef __powerpc64__
		case 68:	/* td */
			if (rd & trap_compare(regs->gpr[ra], regs->gpr[rb]))
				goto trap;
			goto instr_done;
#endif
		case 83:	/* mfmsr */
			if (regs->msr & MSR_PR)
				goto priv;
			op->type = MFMSR;
			op->reg = rd;
			return 0;
		case 146:	/* mtmsr */
			if (regs->msr & MSR_PR)
				goto priv;
			op->type = MTMSR;
			op->reg = rd;
			op->val = 0xffffffff & ~(MSR_ME | MSR_LE);
			return 0;
#ifdef CONFIG_PPC64
		case 178:	/* mtmsrd */
			if (regs->msr & MSR_PR)
				goto priv;
			op->type = MTMSR;
			op->reg = rd;
			/* only MSR_EE and MSR_RI get changed if bit 15 set */
			/* mtmsrd doesn't change MSR_HV, MSR_ME or MSR_LE */
			imm = (instr & 0x10000)? 0x8002: 0xefffffffffffeffeUL;
			op->val = imm;
			return 0;
#endif

		case 19:	/* mfcr */
			regs->gpr[rd] = regs->ccr;
			regs->gpr[rd] &= 0xffffffffUL;
			goto instr_done;

		case 144:	/* mtcrf */
			imm = 0xf0000000UL;
			val = regs->gpr[rd];
			for (sh = 0; sh < 8; ++sh) {
				if (instr & (0x80000 >> sh))
					regs->ccr = (regs->ccr & ~imm) |
						(val & imm);
				imm >>= 4;
			}
			goto instr_done;

		case 339:	/* mfspr */
			spr = ((instr >> 16) & 0x1f) | ((instr >> 6) & 0x3e0);
			switch (spr) {
			case SPRN_XER:	/* mfxer */
				regs->gpr[rd] = regs->xer;
				regs->gpr[rd] &= 0xffffffffUL;
				goto instr_done;
			case SPRN_LR:	/* mflr */
				regs->gpr[rd] = regs->link;
				goto instr_done;
			case SPRN_CTR:	/* mfctr */
				regs->gpr[rd] = regs->ctr;
				goto instr_done;
			default:
				op->type = MFSPR;
				op->reg = rd;
				op->spr = spr;
				return 0;
			}
			break;

		case 467:	/* mtspr */
			spr = ((instr >> 16) & 0x1f) | ((instr >> 6) & 0x3e0);
			switch (spr) {
			case SPRN_XER:	/* mtxer */
				regs->xer = (regs->gpr[rd] & 0xffffffffUL);
				goto instr_done;
			case SPRN_LR:	/* mtlr */
				regs->link = regs->gpr[rd];
				goto instr_done;
			case SPRN_CTR:	/* mtctr */
				regs->ctr = regs->gpr[rd];
				goto instr_done;
			default:
				op->type = MTSPR;
				op->val = regs->gpr[rd];
				op->spr = spr;
				return 0;
			}
			break;

/*
 * Compare instructions
 */
		case 0:	/* cmp */
			val = regs->gpr[ra];
			val2 = regs->gpr[rb];
#ifdef __powerpc64__
			if ((rd & 1) == 0) {
				/* word (32-bit) compare */
				val = (int) val;
				val2 = (int) val2;
			}
#endif
			do_cmp_signed(regs, val, val2, rd >> 2);
			goto instr_done;

		case 32:	/* cmpl */
			val = regs->gpr[ra];
			val2 = regs->gpr[rb];
#ifdef __powerpc64__
			if ((rd & 1) == 0) {
				/* word (32-bit) compare */
				val = (unsigned int) val;
				val2 = (unsigned int) val2;
			}
#endif
			do_cmp_unsigned(regs, val, val2, rd >> 2);
			goto instr_done;

/*
 * Arithmetic instructions
 */
		case 8:	/* subfc */
			add_with_carry(regs, rd, ~regs->gpr[ra],
				       regs->gpr[rb], 1);
			goto arith_done;
#ifdef __powerpc64__
		case 9:	/* mulhdu */
			asm("mulhdu %0,%1,%2" : "=r" (regs->gpr[rd]) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			goto arith_done;
#endif
		case 10:	/* addc */
			add_with_carry(regs, rd, regs->gpr[ra],
				       regs->gpr[rb], 0);
			goto arith_done;

		case 11:	/* mulhwu */
			asm("mulhwu %0,%1,%2" : "=r" (regs->gpr[rd]) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			goto arith_done;

		case 40:	/* subf */
			regs->gpr[rd] = regs->gpr[rb] - regs->gpr[ra];
			goto arith_done;
#ifdef __powerpc64__
		case 73:	/* mulhd */
			asm("mulhd %0,%1,%2" : "=r" (regs->gpr[rd]) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			goto arith_done;
#endif
		case 75:	/* mulhw */
			asm("mulhw %0,%1,%2" : "=r" (regs->gpr[rd]) :
			    "r" (regs->gpr[ra]), "r" (regs->gpr[rb]));
			goto arith_done;

		case 104:	/* neg */
			regs->gpr[rd] = -regs->gpr[ra];
			goto arith_done;

		case 136:	/* subfe */
			add_with_carry(regs, rd, ~regs->gpr[ra], regs->gpr[rb],
				       regs->xer & XER_CA);
			goto arith_done;

		case 138:	/* adde */
			add_with_carry(regs, rd, regs->gpr[ra], regs->gpr[rb],
				       regs->xer & XER_CA);
			goto arith_done;

		case 200:	/* subfze */
			add_with_carry(regs, rd, ~regs->gpr[ra], 0L,
				       regs->xer & XER_CA);
			goto arith_done;

		case 202:	/* addze */
			add_with_carry(regs, rd, regs->gpr[ra], 0L,
				       regs->xer & XER_CA);
			goto arith_done;

		case 232:	/* subfme */
			add_with_carry(regs, rd, ~regs->gpr[ra], -1L,
				       regs->xer & XER_CA);
			goto arith_done;
#ifdef __powerpc64__
		case 233:	/* mulld */
			regs->gpr[rd] = regs->gpr[ra] * regs->gpr[rb];
			goto arith_done;
#endif
		case 234:	/* addme */
			add_with_carry(regs, rd, regs->gpr[ra], -1L,
				       regs->xer & XER_CA);
			goto arith_done;

		case 235:	/* mullw */
			regs->gpr[rd] = (unsigned int) regs->gpr[ra] *
				(unsigned int) regs->gpr[rb];
			goto arith_done;

		case 266:	/* add */
			regs->gpr[rd] = regs->gpr[ra] + regs->gpr[rb];
			goto arith_done;
#ifdef __powerpc64__
		case 457:	/* divdu */
			regs->gpr[rd] = regs->gpr[ra] / regs->gpr[rb];
			goto arith_done;
#endif
		case 459:	/* divwu */
			regs->gpr[rd] = (unsigned int) regs->gpr[ra] /
				(unsigned int) regs->gpr[rb];
			goto arith_done;
#ifdef __powerpc64__
		case 489:	/* divd */
			regs->gpr[rd] = (long int) regs->gpr[ra] /
				(long int) regs->gpr[rb];
			goto arith_done;
#endif
		case 491:	/* divw */
			regs->gpr[rd] = (int) regs->gpr[ra] /
				(int) regs->gpr[rb];
			goto arith_done;


/*
 * Logical instructions
 */
		case 26:	/* cntlzw */
			asm("cntlzw %0,%1" : "=r" (regs->gpr[ra]) :
			    "r" (regs->gpr[rd]));
			goto logical_done;
#ifdef __powerpc64__
		case 58:	/* cntlzd */
			asm("cntlzd %0,%1" : "=r" (regs->gpr[ra]) :
			    "r" (regs->gpr[rd]));
			goto logical_done;
#endif
		case 28:	/* and */
			regs->gpr[ra] = regs->gpr[rd] & regs->gpr[rb];
			goto logical_done;

		case 60:	/* andc */
			regs->gpr[ra] = regs->gpr[rd] & ~regs->gpr[rb];
			goto logical_done;

		case 124:	/* nor */
			regs->gpr[ra] = ~(regs->gpr[rd] | regs->gpr[rb]);
			goto logical_done;

		case 284:	/* xor */
			regs->gpr[ra] = ~(regs->gpr[rd] ^ regs->gpr[rb]);
			goto logical_done;

		case 316:	/* xor */
			regs->gpr[ra] = regs->gpr[rd] ^ regs->gpr[rb];
			goto logical_done;

		case 412:	/* orc */
			regs->gpr[ra] = regs->gpr[rd] | ~regs->gpr[rb];
			goto logical_done;

		case 444:	/* or */
			regs->gpr[ra] = regs->gpr[rd] | regs->gpr[rb];
			goto logical_done;

		case 476:	/* nand */
			regs->gpr[ra] = ~(regs->gpr[rd] & regs->gpr[rb]);
			goto logical_done;

		case 922:	/* extsh */
			regs->gpr[ra] = (signed short) regs->gpr[rd];
			goto logical_done;

		case 954:	/* extsb */
			regs->gpr[ra] = (signed char) regs->gpr[rd];
			goto logical_done;
#ifdef __powerpc64__
		case 986:	/* extsw */
			regs->gpr[ra] = (signed int) regs->gpr[rd];
			goto logical_done;
#endif

/*
 * Shift instructions
 */
		case 24:	/* slw */
			sh = regs->gpr[rb] & 0x3f;
			if (sh < 32)
				regs->gpr[ra] = (regs->gpr[rd] << sh) & 0xffffffffUL;
			else
				regs->gpr[ra] = 0;
			goto logical_done;

		case 536:	/* srw */
			sh = regs->gpr[rb] & 0x3f;
			if (sh < 32)
				regs->gpr[ra] = (regs->gpr[rd] & 0xffffffffUL) >> sh;
			else
				regs->gpr[ra] = 0;
			goto logical_done;

		case 792:	/* sraw */
			sh = regs->gpr[rb] & 0x3f;
			ival = (signed int) regs->gpr[rd];
			regs->gpr[ra] = ival >> (sh < 32 ? sh : 31);
			if (ival < 0 && (sh >= 32 || (ival & ((1ul << sh) - 1)) != 0))
				regs->xer |= XER_CA;
			else
				regs->xer &= ~XER_CA;
			goto logical_done;

		case 824:	/* srawi */
			sh = rb;
			ival = (signed int) regs->gpr[rd];
			regs->gpr[ra] = ival >> sh;
			if (ival < 0 && (ival & ((1ul << sh) - 1)) != 0)
				regs->xer |= XER_CA;
			else
				regs->xer &= ~XER_CA;
			goto logical_done;

#ifdef __powerpc64__
		case 27:	/* sld */
			sh = regs->gpr[rb] & 0x7f;
			if (sh < 64)
				regs->gpr[ra] = regs->gpr[rd] << sh;
			else
				regs->gpr[ra] = 0;
			goto logical_done;

		case 539:	/* srd */
			sh = regs->gpr[rb] & 0x7f;
			if (sh < 64)
				regs->gpr[ra] = regs->gpr[rd] >> sh;
			else
				regs->gpr[ra] = 0;
			goto logical_done;

		case 794:	/* srad */
			sh = regs->gpr[rb] & 0x7f;
			ival = (signed long int) regs->gpr[rd];
			regs->gpr[ra] = ival >> (sh < 64 ? sh : 63);
			if (ival < 0 && (sh >= 64 || (ival & ((1ul << sh) - 1)) != 0))
				regs->xer |= XER_CA;
			else
				regs->xer &= ~XER_CA;
			goto logical_done;

		case 826:	/* sradi with sh_5 = 0 */
		case 827:	/* sradi with sh_5 = 1 */
			sh = rb | ((instr & 2) << 4);
			ival = (signed long int) regs->gpr[rd];
			regs->gpr[ra] = ival >> sh;
			if (ival < 0 && (ival & ((1ul << sh) - 1)) != 0)
				regs->xer |= XER_CA;
			else
				regs->xer &= ~XER_CA;
			goto logical_done;
#endif /* __powerpc64__ */

/*
 * Cache instructions
 */
		case 54:	/* dcbst */
			op->type = MKOP(CACHEOP, DCBST, 0);
			op->ea = xform_ea(instr, regs);
			return 0;

		case 86:	/* dcbf */
			op->type = MKOP(CACHEOP, DCBF, 0);
			op->ea = xform_ea(instr, regs);
			return 0;

		case 246:	/* dcbtst */
			op->type = MKOP(CACHEOP, DCBTST, 0);
			op->ea = xform_ea(instr, regs);
			op->reg = rd;
			return 0;

		case 278:	/* dcbt */
			op->type = MKOP(CACHEOP, DCBTST, 0);
			op->ea = xform_ea(instr, regs);
			op->reg = rd;
			return 0;

		case 982:	/* icbi */
			op->type = MKOP(CACHEOP, ICBI, 0);
			op->ea = xform_ea(instr, regs);
			return 0;
		}
