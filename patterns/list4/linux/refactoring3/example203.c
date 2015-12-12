switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_pmu_spuravoid_pllupdate(&dev->dev->bdev->bus->drv_cc,
					     avoid);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_pmu_spuravoid_pllupdate(&dev->dev->sdev->bus->chipco,
					    avoid);
		break;
#endif
	}
