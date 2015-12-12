static struct omap_hwmod_ocp_if *omap34xx_hwmod_ocp_ifs[] __initdata = {
	&omap3xxx_l3__iva,
	&omap34xx_l4_core__sr1,
	&omap34xx_l4_core__sr2,
	&omap3xxx_l4_core__mailbox,
	&omap3xxx_l4_core__hdq1w,
	&omap3xxx_sad2d__l3,
	&omap3xxx_l4_core__mmu_isp,
#ifdef CONFIG_OMAP_IOMMU_IVA2
	&omap3xxx_l3_main__mmu_iva,
#endif
	NULL
};
