switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		b43_bcma_wireless_core_reset(dev, gmode);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		b43_ssb_wireless_core_reset(dev, gmode);
		break;
#endif
	}
