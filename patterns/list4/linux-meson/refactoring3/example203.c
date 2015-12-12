switch (dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		return bcma_get_drvdata(dev->bdev);
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		return ssb_get_drvdata(dev->sdev);
#endif
	}
