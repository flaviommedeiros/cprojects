#if defined(CONFIG_MACH_ARIESVE) || defined(CONFIG_MACH_ANCORA) || defined(CONFIG_MACH_ANCORA_TMO) || defined(CONFIG_MACH_APACHE)
if(!power_off_done)
#endif
	{
		fsa9480_read_interrupt_register();
	}
