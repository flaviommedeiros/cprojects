switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		hz = ssb_cpu_clock(&bcm47xx_bus.ssb.mipscore) / 2;
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		hz = bcma_cpu_clock(&bcm47xx_bus.bcma.bus.drv_mips) / 2;
		break;
#endif
	}
