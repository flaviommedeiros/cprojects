switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		tmp = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		if (on)
			tmp |= B43_BCMA_IOCTL_MACPHYCLKEN;
		else
			tmp &= ~B43_BCMA_IOCTL_MACPHYCLKEN;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, tmp);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_read32(dev->dev->sdev, SSB_TMSLOW);
		if (on)
			tmp |= B43_TMSLOW_MACPHYCLKEN;
		else
			tmp &= ~B43_TMSLOW_MACPHYCLKEN;
		ssb_write32(dev->dev->sdev, SSB_TMSLOW, tmp);
		break;
#endif
	}
