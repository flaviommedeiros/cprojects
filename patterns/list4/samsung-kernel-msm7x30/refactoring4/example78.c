#ifdef CONFIG_PPC32
if ((addr & 3) || (index > PT_FPSCR)
		    || (child->thread.regs == NULL))
#else
		index = addr >> 3;
