switch ((fpt->thread.fsr & 0x1c000)) {
	/* switch on the contents of the ftt [floating point trap type] field */
#ifdef DEBUG_FPU
	case (1 << 14):
		printk("IEEE_754_exception\n");
		break;
#endif
	case (2 << 14):  /* unfinished_FPop (underflow & co) */
	case (3 << 14):  /* unimplemented_FPop (quad stuff, maybe sqrt) */
		ret = do_mathemu(regs, fpt);
		break;
#ifdef DEBUG_FPU
	case (4 << 14):
		printk("sequence_error (OS bug...)\n");
		break;
	case (5 << 14):
		printk("hardware_error (uhoh!)\n");
		break;
	case (6 << 14):
		printk("invalid_fp_register (user error)\n");
		break;
#endif /* DEBUG_FPU */
	}
