#ifdef CONFIG_MTD_UCLINUX
if (1)
#else
	if (0)
#endif
	{
		if (in_mem(addr, size, memory_start, memory_end))
			return 1;
		if (in_mem(addr, size, memory_mtd_end, physical_mem_end))
			return 1;
# ifndef CONFIG_ROMFS_ON_MTD
		if (0)
# endif
			/* For XIP, allow user space to use pointers within the ROMFS.  */
			if (in_mem(addr, size, memory_mtd_start, memory_mtd_end))
				return 1;
	} else {
		if (in_mem(addr, size, memory_start, physical_mem_end))
			return 1;
	}
