switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		dma->translation = bcma_core_dma_translation(dev->dev->bdev);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		dma->translation = ssb_dma_translation(dev->dev->sdev);
		break;
#endif
	}
