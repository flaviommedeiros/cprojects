#ifdef CONFIG_FAILSAFE_UPGRADE
if (dual_image_on)
			offset = image_second_offset;
		else
#endif
		offset = NFL_BOOT_OS_SIZE;
