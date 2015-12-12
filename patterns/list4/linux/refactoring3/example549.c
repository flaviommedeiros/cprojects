switch (regs->iir & OPCODE1_MASK)
	{
	case OPCODE_LDH_I:
	case OPCODE_LDH_S:
		ret = emulate_ldh(regs, R3(regs->iir));
		break;

	case OPCODE_LDW_I:
	case OPCODE_LDWA_I:
	case OPCODE_LDW_S:
	case OPCODE_LDWA_S:
		ret = emulate_ldw(regs, R3(regs->iir),0);
		break;

	case OPCODE_STH:
		ret = emulate_sth(regs, R2(regs->iir));
		break;

	case OPCODE_STW:
	case OPCODE_STWA:
		ret = emulate_stw(regs, R2(regs->iir),0);
		break;

#ifdef CONFIG_PA20
	case OPCODE_LDD_I:
	case OPCODE_LDDA_I:
	case OPCODE_LDD_S:
	case OPCODE_LDDA_S:
		ret = emulate_ldd(regs, R3(regs->iir),0);
		break;

	case OPCODE_STD:
	case OPCODE_STDA:
		ret = emulate_std(regs, R2(regs->iir),0);
		break;
#endif

	case OPCODE_FLDWX:
	case OPCODE_FLDWS:
	case OPCODE_FLDWXR:
	case OPCODE_FLDWSR:
		flop=1;
		ret = emulate_ldw(regs,FR3(regs->iir),1);
		break;

	case OPCODE_FLDDX:
	case OPCODE_FLDDS:
		flop=1;
		ret = emulate_ldd(regs,R3(regs->iir),1);
		break;

	case OPCODE_FSTWX:
	case OPCODE_FSTWS:
	case OPCODE_FSTWXR:
	case OPCODE_FSTWSR:
		flop=1;
		ret = emulate_stw(regs,FR3(regs->iir),1);
		break;

	case OPCODE_FSTDX:
	case OPCODE_FSTDS:
		flop=1;
		ret = emulate_std(regs,R3(regs->iir),1);
		break;

	case OPCODE_LDCD_I:
	case OPCODE_LDCW_I:
	case OPCODE_LDCD_S:
	case OPCODE_LDCW_S:
		ret = ERR_NOTHANDLED;	/* "undefined", but lets kill them. */
		break;
	}
