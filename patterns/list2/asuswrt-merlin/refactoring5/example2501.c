#ifdef CONFIG_DEBUG_HUNT_FOR_ZERO
if (cpu_pda[cpu].icplb_fault_addr < FIXED_CODE_START)
			strerror = KERN_NOTICE "Jump to NULL address\n";
		else
#endif
			strerror = KERN_NOTICE EXC_0x2D(KERN_NOTICE);
