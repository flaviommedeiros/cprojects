#ifdef CONFIG_MTD_UCLINUX
if (i == SDRAM_RAM_MTD) {
				if ((cplb_data[SDRAM_KERN].end + 1) >
						cplb_data[SDRAM_RAM_MTD].start)
					cplb_data[SDRAM_RAM_MTD].start =
						(cplb_data[i].start &
						 (-2*SIZE_1M)) + SIZE_1M;
				else
					cplb_data[SDRAM_RAM_MTD].start =
						(cplb_data[i].start &
						 (-2*SIZE_1M));
			} else
#endif
				printk(KERN_WARNING
					"Unaligned Start of %s at 0x%X\n",
					cplb_data[i].name, cplb_data[i].start);
