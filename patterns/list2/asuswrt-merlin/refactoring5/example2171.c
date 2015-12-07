#ifdef CONFIG_FAILSAFE_UPGRADE
if (dual_image_on)
			offset = image_second_offset;
		else
#endif
		offset = nfl_boot_os_size(nfl);
