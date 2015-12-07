#ifdef	CONFIG_FAILSAFE_UPGRADE
if (dual_image_on) {
			rfs_off = lookup_flash_rootfs_offset(mtd, &vmlz_off, image_second_offset,
			                                     &trx_size);
			if (trx_size > (image_second_offset - image_first_offset)) {
				printk("sflash size is too small to afford two images.\n");
				dual_image_on = 0;
				image_first_offset = 0;
				image_second_offset = 0;
				rfs_off = lookup_flash_rootfs_offset(mtd, &vmlz_off, size,
				 &trx_size);
			}

			if (dual_image_on && (vmlz_off >= image_second_offset ||
			    vmlz_off == 0 || rfs_off >= image_second_offset)) {
				/* The first linux partition didn't find the rootfs,
				 * set the rootfs to use the same offset with the kernel
				 */
				vmlz_off = image_first_offset;
				rfs_off = image_first_offset;
			}
		} else
#endif	/* CONFIG_FAILSAFE_UPGRADE */
			rfs_off = lookup_flash_rootfs_offset(mtd, &vmlz_off, size, &trx_size);
