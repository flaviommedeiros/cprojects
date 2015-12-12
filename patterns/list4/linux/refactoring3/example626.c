switch (insn.i_format.opcode) {
	case spec_op:
		switch (insn.r_format.func) {
		case jalr_op:
			regs->regs[insn.r_format.rd] =
				regs->cp0_epc + dec_insn.pc_inc +
				dec_insn.next_pc_inc;
			/* Fall through */
		case jr_op:
			/* For R6, JR already emulated in jalr_op */
			if (NO_R6EMU && insn.r_format.func == jr_op)
				break;
			*contpc = regs->regs[insn.r_format.rs];
			return 1;
		}
		break;
	case bcond_op:
		switch (insn.i_format.rt) {
		case bltzal_op:
		case bltzall_op:
			if (NO_R6EMU && (insn.i_format.rs ||
			    insn.i_format.rt == bltzall_op))
				break;

			regs->regs[31] = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
			/* Fall through */
		case bltzl_op:
			if (NO_R6EMU)
				break;
		case bltz_op:
			if ((long)regs->regs[insn.i_format.rs] < 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.i_format.simmediate << 2);
			else
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			return 1;
		case bgezal_op:
		case bgezall_op:
			if (NO_R6EMU && (insn.i_format.rs ||
			    insn.i_format.rt == bgezall_op))
				break;

			regs->regs[31] = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
			/* Fall through */
		case bgezl_op:
			if (NO_R6EMU)
				break;
		case bgez_op:
			if ((long)regs->regs[insn.i_format.rs] >= 0)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.i_format.simmediate << 2);
			else
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;
			return 1;
		}
		break;
	case jalx_op:
		set_isa16_mode(bit);
	case jal_op:
		regs->regs[31] = regs->cp0_epc +
			dec_insn.pc_inc +
			dec_insn.next_pc_inc;
		/* Fall through */
	case j_op:
		*contpc = regs->cp0_epc + dec_insn.pc_inc;
		*contpc >>= 28;
		*contpc <<= 28;
		*contpc |= (insn.j_format.target << 2);
		/* Set microMIPS mode bit: XOR for jalx. */
		*contpc ^= bit;
		return 1;
	case beql_op:
		if (NO_R6EMU)
			break;
	case beq_op:
		if (regs->regs[insn.i_format.rs] ==
		    regs->regs[insn.i_format.rt])
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		return 1;
	case bnel_op:
		if (NO_R6EMU)
			break;
	case bne_op:
		if (regs->regs[insn.i_format.rs] !=
		    regs->regs[insn.i_format.rt])
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		return 1;
	case blezl_op:
		if (!insn.i_format.rt && NO_R6EMU)
			break;
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
				regs->regs[31] = regs->cp0_epc +
					dec_insn.pc_inc;
			*contpc = regs->cp0_epc + dec_insn.pc_inc +
				dec_insn.next_pc_inc;

			return 1;
		}
		if ((long)regs->regs[insn.i_format.rs] <= 0)
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		return 1;
	case bgtzl_op:
		if (!insn.i_format.rt && NO_R6EMU)
			break;
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
				regs->regs[31] = regs->cp0_epc +
					dec_insn.pc_inc;
			*contpc = regs->cp0_epc + dec_insn.pc_inc +
				dec_insn.next_pc_inc;

			return 1;
		}

		if ((long)regs->regs[insn.i_format.rs] > 0)
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				(insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc +
				dec_insn.pc_inc +
				dec_insn.next_pc_inc;
		return 1;
	case cbcond0_op:
	case cbcond1_op:
		if (!cpu_has_mips_r6)
			break;
		if (insn.i_format.rt && !insn.i_format.rs)
			regs->regs[31] = regs->cp0_epc + 4;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		return 1;
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	case lwc2_op: /* This is bbit0 on Octeon */
		if ((regs->regs[insn.i_format.rs] & (1ull<<insn.i_format.rt)) == 0)
			*contpc = regs->cp0_epc + 4 + (insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc + 8;
		return 1;
	case ldc2_op: /* This is bbit032 on Octeon */
		if ((regs->regs[insn.i_format.rs] & (1ull<<(insn.i_format.rt + 32))) == 0)
			*contpc = regs->cp0_epc + 4 + (insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc + 8;
		return 1;
	case swc2_op: /* This is bbit1 on Octeon */
		if (regs->regs[insn.i_format.rs] & (1ull<<insn.i_format.rt))
			*contpc = regs->cp0_epc + 4 + (insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc + 8;
		return 1;
	case sdc2_op: /* This is bbit132 on Octeon */
		if (regs->regs[insn.i_format.rs] & (1ull<<(insn.i_format.rt + 32)))
			*contpc = regs->cp0_epc + 4 + (insn.i_format.simmediate << 2);
		else
			*contpc = regs->cp0_epc + 8;
		return 1;
#else
	case bc6_op:
		/*
		 * Only valid for MIPS R6 but we can still end up
		 * here from a broken userland so just tell emulator
		 * this is not a branch and let it break later on.
		 */
		if  (!cpu_has_mips_r6)
			break;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		return 1;
	case balc6_op:
		if (!cpu_has_mips_r6)
			break;
		regs->regs[31] = regs->cp0_epc + 4;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		return 1;
	case beqzcjic_op:
		if (!cpu_has_mips_r6)
			break;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		return 1;
	case bnezcjialc_op:
		if (!cpu_has_mips_r6)
			break;
		if (!insn.i_format.rs)
			regs->regs[31] = regs->cp0_epc + 4;
		*contpc = regs->cp0_epc + dec_insn.pc_inc +
			dec_insn.next_pc_inc;

		return 1;
#endif
	case cop0_op:
	case cop1_op:
		/* Need to check for R6 bc1nez and bc1eqz branches */
		if (cpu_has_mips_r6 &&
		    ((insn.i_format.rs == bc1eqz_op) ||
		     (insn.i_format.rs == bc1nez_op))) {
			bit = 0;
			switch (insn.i_format.rs) {
			case bc1eqz_op:
				if (get_fpr32(&current->thread.fpu.fpr[insn.i_format.rt], 0) & 0x1)
				    bit = 1;
				break;
			case bc1nez_op:
				if (!(get_fpr32(&current->thread.fpu.fpr[insn.i_format.rt], 0) & 0x1))
				    bit = 1;
				break;
			}
			if (bit)
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					(insn.i_format.simmediate << 2);
			else
				*contpc = regs->cp0_epc +
					dec_insn.pc_inc +
					dec_insn.next_pc_inc;

			return 1;
		}
		/* R2/R6 compatible cop1 instruction. Fall through */
	case cop2_op:
	case cop1x_op:
		if (insn.i_format.rs == bc_op) {
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
			case 0:	/* bc1f */
			case 2:	/* bc1fl */
				if (~fcr31 & (1 << bit))
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						(insn.i_format.simmediate << 2);
				else
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						dec_insn.next_pc_inc;
				return 1;
			case 1:	/* bc1t */
			case 3:	/* bc1tl */
				if (fcr31 & (1 << bit))
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						(insn.i_format.simmediate << 2);
				else
					*contpc = regs->cp0_epc +
						dec_insn.pc_inc +
						dec_insn.next_pc_inc;
				return 1;
			}
		}
		break;
	}
