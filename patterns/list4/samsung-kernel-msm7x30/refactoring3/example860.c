switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		mcore_ssb = &bcm47xx_bus.ssb.mipscore;
		base = mcore_ssb->flash_window;
		lim = mcore_ssb->flash_window_size;
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_cc = &bcm47xx_bus.bcma.bus.drv_cc;
		base = bcma_cc->pflash.window;
		lim = bcma_cc->pflash.window_size;
		break;
#endif
	}
