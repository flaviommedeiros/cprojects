#ifdef CONFIG_FAILSAFE_UPGRADE
if (dual_image_on) {
			bcm947xx_nflash_parts[nparts].size =
				image_second_offset - image_first_offset;
		} else
#endif
		{
			bcm947xx_nflash_parts[nparts].size = nparts ?
				(nfl_boot_os_size(nfl) - nfl_boot_size(nfl)) :
				nfl_boot_os_size(nfl);
		}
