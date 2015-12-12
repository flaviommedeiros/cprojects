struct omap_mbox *omap2_mboxes[] = {
	&mbox_dsp_info,
#ifdef CONFIG_SOC_OMAP2420
	&mbox_iva_info,
#endif
	NULL
};
