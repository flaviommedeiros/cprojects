#ifdef CONFIG_BLK_DEV_INITRD
if (initrd_start)
		ROOT_DEV = Root_RAM0;
	else
#endif
#ifdef	CONFIG_ROOT_NFS
		ROOT_DEV = Root_NFS;
