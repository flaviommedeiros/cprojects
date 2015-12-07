#ifdef NO_DDRCLK_LIMIT
if (ddr_clock_table[idx] != 0) {
#else
			if (CHIPID(sih->chip) == BCM4707_CHIP_ID &&
				sih->chippkg != BCM4709_PKG_ID) {
				void *regs = (void *)si_setcore(sih, NS_DDR23_CORE_ID, 0);
				int ddrtype_ddr3 = 0;
				if (regs) {
					ddrtype_ddr3 = ((si_core_sflags(sih, 0, 0) & DDR_TYPE_MASK)
						== DDR_STAT_DDR3);
				}
				if (ddrtype_ddr3)
					ddrclk_limit = 533;
				else
					ddrclk_limit = 400;
			}
			if (ddr_clock_table[idx] != 0 &&
				(ddrclk_limit == 0 || ddrclock <= ddrclk_limit)) {
#endif
				ddrclk = (uint32 *)(0x1000 + BISZ_OFFSET - 4);
				*ddrclk = ddrclock;
				bootdev = soc_boot_dev((void *)sih);
				if (bootdev == SOC_BOOTDEV_NANDFLASH) {
					__asm__ __volatile__("ldr\tpc,=0x1c000000\n\t");
				} else if (bootdev == SOC_BOOTDEV_SFLASH) {
					__asm__ __volatile__("ldr\tpc,=0x1e000000\n\t");
				}
			}
		}
