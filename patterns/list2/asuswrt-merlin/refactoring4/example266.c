#ifdef CONFIG_XIP_KERNEL
if(!keep_initrd && start < 0x03000000)
#else
	if (!keep_initrd)
#endif
		free_area(start, end, "initrd");
