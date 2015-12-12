switch (insn.i_format.opcode) {
	/*
	 * jr and jalr are in r_format format.
	 */
	case spec_op:
		switch (insn.r_format.func) {
		case jalr_op:
			regs->regs[insn.r_format.rd] = epc + 8;
			/* Fall through */
		case jr_op:
			if (NO_R6EMU && insn.r_format.func == jr_op)
				goto sigill_r6;
			regs->cp0_epc = regs->regs[insn.r_format.rs];
			break;
		}
		break;

	/*
	 * This group contains:
	 * bltz_op, bgez_op, bltzl_op, bgezl_op,
	 * bltzal_op, bgezal_op, bltzall_op, bgezall_op.
	 */
	case bcond_op:
		switch (insn.i_format.rt) {
		case bltzl_op:
			if (NO_R6EMU)
				goto sigill_r6;
		case bltz_op:
			if ((long)regs->regs[insn.i_format.rs] < 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bltzl_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bgezl_op:
			if (NO_R6EMU)
				goto sigill_r6;
		case bgez_op:
			if ((long)regs->regs[insn.i_format.rs] >= 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bgezl_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bltzal_op:
		case bltzall_op:
			if (NO_R6EMU && (insn.i_format.rs ||
			    insn.i_format.rt == bltzall_op)) {
				ret = -SIGILL;
				break;
			}
			regs->regs[31] = epc + 8;
			/*
			 * OK we are here either because we hit a NAL
			 * instruction or because we are emulating an
			 * old bltzal{,l} one. Lets figure out what the
			 * case really is.
			 */
			if (!insn.i_format.rs) {
				/*
				 * NAL or BLTZAL with rs == 0
				 * Doesn't matter if we are R6 or not. The
				 * result is the same
				 */
				regs->cp0_epc += 4 +
					(insn.i_format.simmediate << 2);
				break;
			}
			/* Now do the real thing for non-R6 BLTZAL{,L} */
			if ((long)regs->regs[insn.i_format.rs] < 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bltzall_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bgezal_op:
		case bgezall_op:
			if (NO_R6EMU && (insn.i_format.rs ||
			    insn.i_format.rt == bgezall_op)) {
				ret = -SIGILL;
				break;
			}
			regs->regs[31] = epc + 8;
			/*
			 * OK we are here either because we hit a BAL
			 * instruction or because we are emulating an
			 * old bgezal{,l} one. Lets figure out what the
			 * case really is.
			 */
			if (!insn.i_format.rs) {
				/*
				 * BAL or BGEZAL with rs == 0
				 * Doesn't matter if we are R6 or not. The
				 * result is the same
				 */
				regs->cp0_epc += 4 +
					(insn.i_format.simmediate << 2);
				break;
			}
			/* Now do the real thing for non-R6 BGEZAL{,L} */
			if ((long)regs->regs[insn.i_format.rs] >= 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bgezall_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bposge32_op:
			if (!cpu_has_dsp)
				goto sigill_dsp;

			dspcontrol = rddsp(0x01);

			if (dspcontrol >= 32) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;
		}
		break;

	/*
	 * These are unconditional and in j_format.
	 */
	case jal_op:
		regs->regs[31] = regs->cp0_epc + 8;
	case j_op:
		epc += 4;
		epc >>= 28;
		epc <<= 28;
		epc |= (insn.j_format.target << 2);
		regs->cp0_epc = epc;
		if (insn.i_format.opcode == jalx_op)
			set_isa16_mode(regs->cp0_epc);
		break;

	/*
	 * These are conditional and in i_format.
	 */
	case beql_op:
		if (NO_R6EMU)
			goto sigill_r6;
	case beq_op:
		if (regs->regs[insn.i_format.rs] ==
		    regs->regs[insn.i_format.rt]) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == beql_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case bnel_op:
		if (NO_R6EMU)
			goto sigill_r6;
	case bne_op:
		if (regs->regs[insn.i_format.rs] !=
		    regs->regs[insn.i_format.rt]) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == bnel_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case blezl_op: /* not really i_format */
		if (!insn.i_format.rt && NO_R6EMU)
			goto sigill_r6;
	case blez_op:
		/*
		 * Compact branches for R6 for the
		 * blez and blezl opcodes.
		 * BLEZ  | rs = 0 | rt != 0  == BLEZALC
		 * BLEZ  | rs = rt != 0      == BGEZALC
		 * BLEZ  | rs != 0 | rt != 0 == BGEUC
		 * BLEZL | rs = 0 | rt != 0  == BLEZC
		 * BLEZL | rs = rt != 0      == BGEZC
		 * BLEZL | rs != 0 | rt != 0 == BGEC
		 *
		 * For real BLEZ{,L}, rt is always 0.
		 */

		if (cpu_has_mips_r6 && insn.i_format.rt) {
			if ((insn.i_format.opcode == blez_op) &&
			    ((!insn.i_format.rs && insn.i_format.rt) ||
			     (insn.i_format.rs == insn.i_format.rt)))
				regs->regs[31] = epc + 4;
			regs->cp0_epc += 8;
			break;
		}
		/* rt field assumed to be zero */
		if ((long)regs->regs[insn.i_format.rs] <= 0) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == blezl_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case bgtzl_op:
		if (!insn.i_format.rt && NO_R6EMU)
			goto sigill_r6;
	case bgtz_op:
		/*
		 * Compact branches for R6 for the
		 * bgtz and bgtzl opcodes.
		 * BGTZ  | rs = 0 | rt != 0  == BGTZALC
		 * BGTZ  | rs = rt != 0      == BLTZALC
		 * BGTZ  | rs != 0 | rt != 0 == BLTUC
		 * BGTZL | rs = 0 | rt != 0  == BGTZC
		 * BGTZL | rs = rt != 0      == BLTZC
		 * BGTZL | rs != 0 | rt != 0 == BLTC
		 *
		 * *ZALC varint for BGTZ &&& rt != 0
		 * For real GTZ{,L}, rt is always 0.
		 */
		if (cpu_has_mips_r6 && insn.i_format.rt) {
			if ((insn.i_format.opcode == blez_op) &&
			    ((!insn.i_format.rs && insn.i_format.rt) ||
			    (insn.i_format.rs == insn.i_format.rt)))
				regs->regs[31] = epc + 4;
			regs->cp0_epc += 8;
			break;
		}

		/* rt field assumed to be zero */
		if ((long)regs->regs[insn.i_format.rs] > 0) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.opcode == bgtzl_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	/*
	 * And now the FPA/cp1 branch instructions.
	 */
	case cop1_op:
		if (cpu_has_mips_r6 &&
		    ((insn.i_format.rs == bc1eqz_op) ||
		     (insn.i_format.rs == bc1nez_op))) {
			if (!used_math()) { /* First time FPU user */
				ret = init_fpu();
				if (ret && NO_R6EMU) {
					ret = -ret;
					break;
				}
				ret = 0;
				set_used_math();
			}
			lose_fpu(1);    /* Save FPU state for the emulator. */
			reg = insn.i_format.rt;
			bit = 0;
			switch (insn.i_format.rs) {
			case bc1eqz_op:
				/* Test bit 0 */
				if (get_fpr32(&current->thread.fpu.fpr[reg], 0)
				    & 0x1)
					bit = 1;
				break;
			case bc1nez_op:
				/* Test bit 0 */
				if (!(get_fpr32(&current->thread.fpu.fpr[reg], 0)
				      & 0x1))
					bit = 1;
				break;
			}
			own_fpu(1);
			if (bit)
				epc = epc + 4 +
					(insn.i_format.simmediate << 2);
			else
				epc += 8;
			regs->cp0_epc = epc;

			break;
		} else {

			preempt_disable();
			if (is_fpu_owner())
			        fcr31 = read_32bit_cp1_register(CP1_STATUS);
			else
				fcr31 = current->thread.fpu.fcr31;
			preempt_enable();

			bit = (insn.i_format.rt >> 2);
			bit += (bit != 0);
			bit += 23;
			switch (insn.i_format.rt & 3) {
			case 0: /* bc1f */
			case 2: /* bc1fl */
				if (~fcr31 & (1 << bit)) {
					epc = epc + 4 +
						(insn.i_format.simmediate << 2);
					if (insn.i_format.rt == 2)
						ret = BRANCH_LIKELY_TAKEN;
				} else
					epc += 8;
				regs->cp0_epc = epc;
				break;

			case 1: /* bc1t */
			case 3: /* bc1tl */
				if (fcr31 & (1 << bit)) {
					epc = epc + 4 +
						(insn.i_format.simmediate << 2);
					if (insn.i_format.rt == 3)
						ret = BRANCH_LIKELY_TAKEN;
				} else
					epc += 8;
				regs->cp0_epc = epc;
				break;
			}
			break;
		}
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	case lwc2_op: /* This is bbit0 on Octeon */
		if ((regs->regs[insn.i_format.rs] & (1ull<<insn.i_format.rt))
		     == 0)
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
	case ldc2_op: /* This is bbit032 on Octeon */
		if ((regs->regs[insn.i_format.rs] &
		    (1ull<<(insn.i_format.rt+32))) == 0)
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
	case swc2_op: /* This is bbit1 on Octeon */
		if (regs->regs[insn.i_format.rs] & (1ull<<insn.i_format.rt))
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
	case sdc2_op: /* This is bbit132 on Octeon */
		if (regs->regs[insn.i_format.rs] &
		    (1ull<<(insn.i_format.rt+32)))
			epc = epc + 4 + (insn.i_format.simmediate << 2);
		else
			epc += 8;
		regs->cp0_epc = epc;
		break;
#else
	case bc6_op:
		/* Only valid for MIPS R6 */
		if (!cpu_has_mips_r6) {
			ret = -SIGILL;
			break;
		}
		regs->cp0_epc += 8;
		break;
	case balc6_op:
		if (!cpu_has_mips_r6) {
			ret = -SIGILL;
			break;
		}
		/* Compact branch: BALC */
		regs->regs[31] = epc + 4;
		epc += 4 + (insn.i_format.simmediate << 2);
		regs->cp0_epc = epc;
		break;
	case beqzcjic_op:
		if (!cpu_has_mips_r6) {
			ret = -SIGILL;
			break;
		}
		/* Compact branch: BEQZC || JIC */
		regs->cp0_epc += 8;
		break;
	case bnezcjialc_op:
		if (!cpu_has_mips_r6) {
			ret = -SIGILL;
			break;
		}
		/* Compact branch: BNEZC || JIALC */
		if (insn.i_format.rs)
			regs->regs[31] = epc + 4;
		regs->cp0_epc += 8;
		break;
#endif
	case cbcond0_op:
	case cbcond1_op:
		/* Only valid for MIPS R6 */
		if (!cpu_has_mips_r6) {
			ret = -SIGILL;
			break;
		}
		/*
		 * Compact branches:
		 * bovc, beqc, beqzalc, bnvc, bnec, bnezlac
		 */
		if (insn.i_format.rt && !insn.i_format.rs)
			regs->regs[31] = epc + 4;
		regs->cp0_epc += 8;
		break;
	}
