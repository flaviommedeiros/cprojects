if ((hp->happy_bursts & DMA_BURST64) &&
	    ((hp->happy_flags & HFLAG_PCI) != 0
#ifdef CONFIG_SBUS
	     || sbus_can_burst64(hp->happy_dev)
#endif
	     || 0)) {
		u32 gcfg = GREG_CFG_BURST64;

		/* I have no idea if I should set the extended
		 * transfer mode bit for Cheerio, so for now I
		 * do not.  -DaveM
		 */
#ifdef CONFIG_SBUS
		if ((hp->happy_flags & HFLAG_PCI) == 0 &&
		    sbus_can_dma_64bit(hp->happy_dev)) {
			sbus_set_sbus64(hp->happy_dev,
					hp->happy_bursts);
			gcfg |= GREG_CFG_64BIT;
		}
#endif

		HMD(("64>"));
		hme_write32(hp, gregs + GREG_CFG, gcfg);
	} else if (hp->happy_bursts & DMA_BURST32) {
		HMD(("32>"));
		hme_write32(hp, gregs + GREG_CFG, GREG_CFG_BURST32);
	} else if (hp->happy_bursts & DMA_BURST16) {
		HMD(("16>"));
		hme_write32(hp, gregs + GREG_CFG, GREG_CFG_BURST16);
	} else {
		HMD(("XXX>"));
		hme_write32(hp, gregs + GREG_CFG, 0);
	}
