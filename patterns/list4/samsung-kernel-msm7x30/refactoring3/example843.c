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
	 	case bltz_op:
		case bltzl_op:
			if ((long)regs->regs[insn.i_format.rs] < 0) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == bltzl_op)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case bgez_op:
		case bgezl_op:
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
			regs->regs[31] = epc + 8;
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
			regs->regs[31] = epc + 8;
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
				goto sigill;

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
		break;

	/*
	 * These are conditional and in i_format.
	 */
	case beq_op:
	case beql_op:
		if (regs->regs[insn.i_format.rs] ==
		    regs->regs[insn.i_format.rt]) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.rt == beql_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case bne_op:
	case bnel_op:
		if (regs->regs[insn.i_format.rs] !=
		    regs->regs[insn.i_format.rt]) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.rt == bnel_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case blez_op: /* not really i_format */
	case blezl_op:
		/* rt field assumed to be zero */
		if ((long)regs->regs[insn.i_format.rs] <= 0) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.rt == bnel_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	case bgtz_op:
	case bgtzl_op:
		/* rt field assumed to be zero */
		if ((long)regs->regs[insn.i_format.rs] > 0) {
			epc = epc + 4 + (insn.i_format.simmediate << 2);
			if (insn.i_format.rt == bnel_op)
				ret = BRANCH_LIKELY_TAKEN;
		} else
			epc += 8;
		regs->cp0_epc = epc;
		break;

	/*
	 * And now the FPA/cp1 branch instructions.
	 */
	case cop1_op:
		preempt_disable();
		if (is_fpu_owner())
			asm volatile("cfc1\t%0,$31" : "=r" (fcr31));
		else
			fcr31 = current->thread.fpu.fcr31;
		preempt_enable();

		bit = (insn.i_format.rt >> 2);
		bit += (bit != 0);
		bit += 23;
		switch (insn.i_format.rt & 3) {
		case 0:	/* bc1f */
		case 2:	/* bc1fl */
			if (~fcr31 & (1 << bit)) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == 2)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;

		case 1:	/* bc1t */
		case 3:	/* bc1tl */
			if (fcr31 & (1 << bit)) {
				epc = epc + 4 + (insn.i_format.simmediate << 2);
				if (insn.i_format.rt == 3)
					ret = BRANCH_LIKELY_TAKEN;
			} else
				epc += 8;
			regs->cp0_epc = epc;
			break;
		}
		break;
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
#endif
	}
