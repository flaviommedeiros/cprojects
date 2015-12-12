static struct musb_hdrc_config	puv3_usb_config[] = {
	{
		.num_eps = 16,
		.multipoint = 1,
#ifdef CONFIG_USB_INVENTRA_DMA
		.dma = 1,
		.dma_channels = 8,
#endif
	},
};
