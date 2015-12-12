if (mfd->panel_info.pdest == DISPLAY_1) {
				dma2_cfg_reg |= DMA_MDDI_DMAOUT_LCD_SEL_PRIMARY;
				mddi_ld_param = 0;
#ifdef MDDI_HOST_WINDOW_WORKAROUND
				mddi_window_adjust(mfd, iBuf->dma_x,
						   iBuf->dma_w - 1, iBuf->dma_y,
						   iBuf->dma_h - 1);
#endif
			} else {
				dma2_cfg_reg |=
				    DMA_MDDI_DMAOUT_LCD_SEL_SECONDARY;
				mddi_ld_param = 1;
#ifdef MDDI_HOST_WINDOW_WORKAROUND
				mddi_window_adjust(mfd, iBuf->dma_x,
						   iBuf->dma_w - 1, iBuf->dma_y,
						   iBuf->dma_h - 1);
#endif
			}
#endif
