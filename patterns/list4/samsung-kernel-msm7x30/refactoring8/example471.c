static struct sh_mobile_lcdc_info lcdc_info = {
	.meram_dev = &meram_info,
	.ch[0] = {
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.lcd_modes = ap4evb_lcdc_modes,
		.num_modes = ARRAY_SIZE(ap4evb_lcdc_modes),
		.meram_cfg = &lcd_meram_cfg,
#ifdef CONFIG_AP4EVB_QHD
		.tx_dev = &mipidsi0_device,
#endif
	}
};
