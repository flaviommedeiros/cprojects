if (hwreg_present(&tt_scc_dma.dma_ctrl) &&
#if 0
	    /* This test sucks! Who knows some better? */
	    (tt_scc_dma.dma_ctrl = 0x01, (tt_scc_dma.dma_ctrl & 1) == 1) &&
	    (tt_scc_dma.dma_ctrl = 0x00, (tt_scc_dma.dma_ctrl & 1) == 0)
#else
	    !MACH_IS_MEDUSA
#endif
	    ) {
		ATARIHW_SET(SCC_DMA);
		printk("SCC_DMA ");
	}
