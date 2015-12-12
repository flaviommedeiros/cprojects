switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_cc = &dev->dev->bdev->bus->drv_cc;

		bcma_cc_write32(bcma_cc, BCMA_CC_CHIPCTL_ADDR, 0);
		bcma_cc_mask32(bcma_cc, BCMA_CC_CHIPCTL_DATA, ~0x4);
		bcma_cc_set32(bcma_cc, BCMA_CC_CHIPCTL_DATA, 0x4);
		bcma_cc_mask32(bcma_cc, BCMA_CC_CHIPCTL_DATA, ~0x4);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_cc = &dev->dev->sdev->bus->chipco;

		chipco_write32(ssb_cc, SSB_CHIPCO_CHIPCTL_ADDR, 0);
		chipco_mask32(ssb_cc, SSB_CHIPCO_CHIPCTL_DATA, ~0x4);
		chipco_set32(ssb_cc, SSB_CHIPCO_CHIPCTL_DATA, 0x4);
		chipco_mask32(ssb_cc, SSB_CHIPCO_CHIPCTL_DATA, ~0x4);
		break;
#endif
	}
