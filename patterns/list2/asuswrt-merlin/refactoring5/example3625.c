#ifdef CONFIG_FAILSAFE_UPGRADE
if (dual_image_on && (trx_size >= (image_second_offset - image_first_offset))) {
			bcm947xx_nflash_parts[nparts].size = nparts ?
				(nfl_boot_os_size(nfl) - nfl_boot_size(nfl)) :
				nfl_boot_os_size(nfl);
			dual_image_on = 0;
			image_first_offset = 0;
			image_second_offset = 0;
		}
