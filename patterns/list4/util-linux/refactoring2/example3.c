#ifdef __linux__
if (ver >= KERNEL_VERSION (2,6,0) ||
		   (ver >= KERNEL_VERSION (2,4,18) && ver < KERNEL_VERSION (2,5,0)))
#endif
			if (ioctl(fd, BLKGETSIZE64, bytes) >= 0)
				return 0;
