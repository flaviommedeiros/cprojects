#ifdef CONFIG_BLK_DEV_INITRD
if (initrd_start)
		ROOT_DEV = Root_RAM0;
	else
#endif
		ROOT_DEV = DEFAULT_ROOT_DEVICE;
