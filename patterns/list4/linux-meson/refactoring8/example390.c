static struct omap_hwmod_ocp_if *omap36xx_hwmod_ocp_ifs[] __initdata = {
	&omap3xxx_l3__iva,
	&omap36xx_l4_per__uart4,
	&omap3xxx_dss__l3,
	&omap3xxx_l4_core__dss,
	&omap36xx_l4_core__sr1,
	&omap36xx_l4_core__sr2,
	&omap3xxx_usbhsotg__l3,
	&omap3xxx_l4_core__usbhsotg,
	&omap3xxx_l4_core__mailbox,
	&omap3xxx_usb_host_hs__l3_main_2,
	&omap3xxx_l4_core__usb_host_hs,
	&omap3xxx_l4_core__usb_tll_hs,
	&omap3xxx_l4_core__es3plus_mmc1,
	&omap3xxx_l4_core__es3plus_mmc2,
	&omap3xxx_l4_core__hdq1w,
	&omap3xxx_sad2d__l3,
	&omap3xxx_l4_core__mmu_isp,
#ifdef CONFIG_OMAP_IOMMU_IVA2
	&omap3xxx_l3_main__mmu_iva,
#endif
	NULL
};
