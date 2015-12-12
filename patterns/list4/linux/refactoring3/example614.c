switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		if (bcm47xx_bus.ssb.chip_id == 0x4785)
			write_c0_diag4(1 << 22);
		ssb_watchdog_timer_set(&bcm47xx_bus.ssb, 1);
		if (bcm47xx_bus.ssb.chip_id == 0x4785) {
			__asm__ __volatile__(
				".set\tmips3\n\t"
				"sync\n\t"
				"wait\n\t"
				".set\tmips0");
		}
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchdog_timer_set(&bcm47xx_bus.bcma.bus.drv_cc, 1);
		break;
#endif
	}
