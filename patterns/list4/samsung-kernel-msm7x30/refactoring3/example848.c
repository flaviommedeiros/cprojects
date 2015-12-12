switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		if (ssb_chipco_available(&bcm47xx_bus.ssb.chipco) &&
		    ((unsigned)gpio >= BCM47XX_CHIPCO_GPIO_LINES))
			return;

		if (ssb_extif_available(&bcm47xx_bus.ssb.extif) &&
		    ((unsigned)gpio >= BCM47XX_EXTIF_GPIO_LINES))
			return;

		clear_bit(gpio, gpio_in_use);
		return;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		if (gpio >= BCM47XX_CHIPCO_GPIO_LINES)
			return;

		clear_bit(gpio, gpio_in_use);
		return;
#endif
	}
