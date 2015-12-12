switch (regs->iir & OPCODE2_MASK)
	{
	case OPCODE_FLDD_L:
		flop=1;
		ret = emulate_ldd(regs,R2(regs->iir),1);
		break;
	case OPCODE_FSTD_L:
		flop=1;
		ret = emulate_std(regs, R2(regs->iir),1);
		break;

#ifdef CONFIG_PA20
	case OPCODE_LDD_L:
		ret = emulate_ldd(regs, R2(regs->iir),0);
		break;
	case OPCODE_STD_L:
		ret = emulate_std(regs, R2(regs->iir),0);
		break;
#endif
	}
