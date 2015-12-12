switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		/* Unset reset bit (with forcing clock) */
		tmp = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		tmp &= ~B43_BCMA_IOCTL_PHY_RESET;
		tmp &= ~B43_BCMA_IOCTL_PHY_CLKEN;
		tmp |= BCMA_IOCTL_FGC;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, tmp);
		udelay(1);

		/* Do not force clock anymore */
		tmp = bcma_aread32(dev->dev->bdev, BCMA_IOCTL);
		tmp &= ~BCMA_IOCTL_FGC;
		tmp |= B43_BCMA_IOCTL_PHY_CLKEN;
		bcma_awrite32(dev->dev->bdev, BCMA_IOCTL, tmp);
		udelay(1);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		/* Unset reset bit (with forcing clock) */
		tmp = ssb_read32(dev->dev->sdev, SSB_TMSLOW);
		tmp &= ~B43_TMSLOW_PHYRESET;
		tmp &= ~B43_TMSLOW_PHYCLKEN;
		tmp |= SSB_TMSLOW_FGC;
		ssb_write32(dev->dev->sdev, SSB_TMSLOW, tmp);
		ssb_read32(dev->dev->sdev, SSB_TMSLOW); /* flush */
		usleep_range(1000, 2000);

		tmp = ssb_read32(dev->dev->sdev, SSB_TMSLOW);
		tmp &= ~SSB_TMSLOW_FGC;
		tmp |= B43_TMSLOW_PHYCLKEN;
		ssb_write32(dev->dev->sdev, SSB_TMSLOW, tmp);
		ssb_read32(dev->dev->sdev, SSB_TMSLOW); /* flush */
		usleep_range(1000, 2000);
		break;
#endif
	}
