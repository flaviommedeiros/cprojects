static struct atmel_pcm_dma_params ssc_dma_params[NUM_SSC_DEVICES][2] = {
	{{
	.name		= "SSC0 PCM out",
	.pdc		= &pdc_tx_reg,
	.mask		= &ssc_tx_mask,
	},
	{
	.name		= "SSC0 PCM in",
	.pdc		= &pdc_rx_reg,
	.mask		= &ssc_rx_mask,
	} },
#if NUM_SSC_DEVICES == 3
	{{
	.name		= "SSC1 PCM out",
	.pdc		= &pdc_tx_reg,
	.mask		= &ssc_tx_mask,
	},
	{
	.name		= "SSC1 PCM in",
	.pdc		= &pdc_rx_reg,
	.mask		= &ssc_rx_mask,
	} },
	{{
	.name		= "SSC2 PCM out",
	.pdc		= &pdc_tx_reg,
	.mask		= &ssc_tx_mask,
	},
	{
	.name		= "SSC2 PCM in",
	.pdc		= &pdc_rx_reg,
	.mask		= &ssc_rx_mask,
	} },
#endif
};
