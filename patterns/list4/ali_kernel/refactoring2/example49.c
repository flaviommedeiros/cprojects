#if defined(CONFIG_SYSCTL) || defined(CONFIG_PROCESS_DEBUG)
if (sysctl_userprocess_debug)
#endif
	{
		printk("User process fault: interruption code 0x%lX\n",
		       int_code);
		printk("failing address: %lX\n", address);
		show_regs(regs);
	}
