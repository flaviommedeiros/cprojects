# ifndef CONFIG_ROMFS_ON_MTD
if (0)
# endif
			/* For XIP, allow user space to use pointers within the ROMFS.  */
			if (in_mem(addr, size, memory_mtd_start, memory_mtd_end))
				return 1;
