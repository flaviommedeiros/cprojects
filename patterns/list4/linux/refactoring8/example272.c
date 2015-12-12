static struct sync_port ports[] = {
	{
		.regi_sser		= SYNCSER_INST0,
		.regi_dmaout		= OUT_DMA_INST0,
		.regi_dmain		= IN_DMA_INST0,
		.use_dma		= PORT0_DMA,
		.dma_in_intr_vect	= DMA_IN_INTR_VECT0,
		.dma_out_intr_vect	= DMA_OUT_INTR_VECT0,
		.dma_in_nbr		= DMA_IN_NBR0,
		.dma_out_nbr		= DMA_OUT_NBR0,
		.req_dma		= REQ_DMA_SYNCSER0,
		.syncser_intr_vect	= SYNCSER_INTR_VECT0,
	},
#ifdef CONFIG_ETRAXFS
	{
		.regi_sser		= SYNCSER_INST1,
		.regi_dmaout		= regi_dma6,
		.regi_dmain		= regi_dma7,
		.use_dma		= PORT1_DMA,
		.dma_in_intr_vect	= DMA_IN_INTR_VECT1,
		.dma_out_intr_vect	= DMA_OUT_INTR_VECT1,
		.dma_in_nbr		= DMA_IN_NBR1,
		.dma_out_nbr		= DMA_OUT_NBR1,
		.req_dma		= REQ_DMA_SYNCSER1,
		.syncser_intr_vect	= SYNCSER_INTR_VECT1,
	},
#endif
};
