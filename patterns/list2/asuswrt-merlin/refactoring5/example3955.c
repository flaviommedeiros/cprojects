#ifdef CONFIG_DEBUG_HUNT_FOR_ZERO
if (cpu_pda[cpu].dcplb_fault_addr < FIXED_CODE_START)
			strerror = KERN_NOTICE "NULL pointer access\n";
		else
#endif
			strerror = KERN_NOTICE EXC_0x27(KERN_NOTICE);
