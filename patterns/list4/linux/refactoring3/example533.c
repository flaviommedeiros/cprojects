switch (get_ins_reg_width(ins_addr)) {
	case 1:
		return *get_reg_w8(reg, prf.rex, regs);

	case 2:
		return *(unsigned short *)get_reg_w32(reg, regs);

	case 4:
		return *(unsigned int *)get_reg_w32(reg, regs);

#ifdef __amd64__
	case 8:
		return *(unsigned long *)get_reg_w32(reg, regs);
#endif

	default:
		printk(KERN_ERR "mmiotrace: Error width# %d\n", reg);
	}
