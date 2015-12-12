if (nx_enabled)
		printk(KERN_INFO "NX (Execute Disable) protection: active\n");
#ifdef CONFIG_X86_32
	else
	if (exec_shield)
		printk(KERN_INFO "Using x86 segment limits to approximate "
			"NX protection\n");
#endif
