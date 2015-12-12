switch (dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_set_drvdata(dev->bdev, wldev);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_set_drvdata(dev->sdev, wldev);
		break;
#endif
	}
