switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		if (ssb_chipco_available(&bcm47xx_bus.ssb.chipco))
			return ssb_mips_irq(bcm47xx_bus.ssb.chipco.dev) + 2;
		else if (ssb_extif_available(&bcm47xx_bus.ssb.extif))
			return ssb_mips_irq(bcm47xx_bus.ssb.extif.dev) + 2;
		else
			return -EINVAL;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		return bcma_core_mips_irq(bcm47xx_bus.bcma.bus.drv_cc.core) + 2;
#endif
	}
