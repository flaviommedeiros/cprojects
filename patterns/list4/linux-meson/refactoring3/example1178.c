switch (insn.i_format.opcode) {

		/*
		 * This group contains:
		 * jr and jalr are in r_format format.
		 */
	case spec_op:
		switch (insn.r_format.func) {
		case jr_op:
		case jalr_op:
			break;
		default:
			goto insn_ok;
		}

		/*
		 * This group contains:
		 * bltz_op, bgez_op, bltzl_op, bgezl_op,
		 * bltzal_op, bgezal_op, bltzall_op, bgezall_op.
		 */
	case bcond_op:

		/*
		 * These are unconditional and in j_format.
		 */
	case jal_op:
	case j_op:

		/*
		 * These are conditional and in i_format.
		 */
	case beq_op:
	case beql_op:
	case bne_op:
	case bnel_op:
	case blez_op:
	case blezl_op:
	case bgtz_op:
	case bgtzl_op:

		/*
		 * These are the FPA/cp1 branch instructions.
		 */
	case cop1_op:

#ifdef CONFIG_CPU_CAVIUM_OCTEON
	case lwc2_op: /* This is bbit0 on Octeon */
	case ldc2_op: /* This is bbit032 on Octeon */
	case swc2_op: /* This is bbit1 on Octeon */
	case sdc2_op: /* This is bbit132 on Octeon */
#endif
		return 1;
	default:
		break;
	}
