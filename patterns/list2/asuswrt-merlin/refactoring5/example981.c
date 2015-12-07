#ifdef CONFIG_FAILSAFE_UPGRADE
if (dual_image_on)
			bcm947xx_nflash_parts[nparts].size = image_second_offset - shift;
		else
#endif
		bcm947xx_nflash_parts[nparts].size = NFL_BOOT_OS_SIZE - shift;
