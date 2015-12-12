switch (dev->dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		cc = &dev->dev->bdev->bus->drv_cc;
		if (dev->dev->chip_id == 43224 || dev->dev->chip_id == 43225) {
			if (avoid) {
				bcma_chipco_pll_write(cc, 0x0, 0x11500010);
				bcma_chipco_pll_write(cc, 0x1, 0x000C0C06);
				bcma_chipco_pll_write(cc, 0x2, 0x0F600a08);
				bcma_chipco_pll_write(cc, 0x3, 0x00000000);
				bcma_chipco_pll_write(cc, 0x4, 0x2001E920);
				bcma_chipco_pll_write(cc, 0x5, 0x88888815);
			} else {
				bcma_chipco_pll_write(cc, 0x0, 0x11100010);
				bcma_chipco_pll_write(cc, 0x1, 0x000c0c06);
				bcma_chipco_pll_write(cc, 0x2, 0x03000a08);
				bcma_chipco_pll_write(cc, 0x3, 0x00000000);
				bcma_chipco_pll_write(cc, 0x4, 0x200005c0);
				bcma_chipco_pll_write(cc, 0x5, 0x88888815);
			}
			pmu_ctl = BCMA_CC_PMU_CTL_PLL_UPD;
		} else if (dev->dev->chip_id == 0x4716) {
			if (avoid) {
				bcma_chipco_pll_write(cc, 0x0, 0x11500060);
				bcma_chipco_pll_write(cc, 0x1, 0x080C0C06);
				bcma_chipco_pll_write(cc, 0x2, 0x0F600000);
				bcma_chipco_pll_write(cc, 0x3, 0x00000000);
				bcma_chipco_pll_write(cc, 0x4, 0x2001E924);
				bcma_chipco_pll_write(cc, 0x5, 0x88888815);
			} else {
				bcma_chipco_pll_write(cc, 0x0, 0x11100060);
				bcma_chipco_pll_write(cc, 0x1, 0x080c0c06);
				bcma_chipco_pll_write(cc, 0x2, 0x03000000);
				bcma_chipco_pll_write(cc, 0x3, 0x00000000);
				bcma_chipco_pll_write(cc, 0x4, 0x200005c0);
				bcma_chipco_pll_write(cc, 0x5, 0x88888815);
			}
			pmu_ctl = BCMA_CC_PMU_CTL_PLL_UPD |
				  BCMA_CC_PMU_CTL_NOILPONW;
		} else if (dev->dev->chip_id == 0x4322 ||
			   dev->dev->chip_id == 0x4340 ||
			   dev->dev->chip_id == 0x4341) {
			bcma_chipco_pll_write(cc, 0x0, 0x11100070);
			bcma_chipco_pll_write(cc, 0x1, 0x1014140a);
			bcma_chipco_pll_write(cc, 0x5, 0x88888854);
			if (avoid)
				bcma_chipco_pll_write(cc, 0x2, 0x05201828);
			else
				bcma_chipco_pll_write(cc, 0x2, 0x05001828);
			pmu_ctl = BCMA_CC_PMU_CTL_PLL_UPD;
		} else {
			return;
		}
		bcma_cc_set32(cc, BCMA_CC_PMU_CTL, pmu_ctl);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_pmu_spuravoid_pllupdate(&dev->dev->sdev->bus->chipco,
					    avoid);
		break;
#endif
	}
