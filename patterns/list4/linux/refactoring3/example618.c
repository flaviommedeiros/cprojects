switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		/* Nothing to do */
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		/* The BCM4706 has a problem with the CPU wait instruction.
		 * When r4k_wait or r4k_wait_irqoff is used will just hang and
		 * not return from a msleep(). Removing the cpu_wait
		 * functionality is a workaround for this problem. The BCM4716
		 * does not have this problem.
		 */
		if (bcm47xx_bus.bcma.bus.chipinfo.id == BCMA_CHIP_ID_BCM4706)
			cpu_wait = NULL;
		break;
#endif
	}
