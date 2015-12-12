switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		b43err(dev->wl,
		       "Putting PHY into reset not supported on BCMA\n");
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		tmp = ssb_read32(dev->dev->sdev, SSB_TMSLOW);
		tmp &= ~B43_TMSLOW_GMODE;
		tmp |= B43_TMSLOW_PHYRESET;
		tmp |= SSB_TMSLOW_FGC;
		ssb_write32(dev->dev->sdev, SSB_TMSLOW, tmp);
		msleep(1);

		tmp = ssb_read32(dev->dev->sdev, SSB_TMSLOW);
		tmp &= ~SSB_TMSLOW_FGC;
		tmp |= B43_TMSLOW_PHYRESET;
		ssb_write32(dev->dev->sdev, SSB_TMSLOW, tmp);
		msleep(1);

		break;
#endif
	}
