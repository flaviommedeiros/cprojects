static const struct of_device_id stmmac_dt_ids[] = {
#ifdef CONFIG_DWMAC_MESON
	{ .compatible = "amlogic,meson6-dwmac", /*.data = &meson6_dwmac_data*/},
	{ .compatible = "amlogic,meson8-rmii-dwmac", /*s802 100m mode this chip have no gmac not support 1000m*/},
	{ .compatible = "amlogic,meson8m2-rgmii-dwmac",},// s812 chip 1000m mode
	{ .compatible = "amlogic,meson8m2-rmii-dwmac", .data = &meson6_dwmac_data },// s812 chip 100m mode
	{ .compatible = "amlogic,meson8b-rgmii-dwmac", },// s805 chip 1000m mode
	{ .compatible = "amlogic,mesong9tv-rmii-dwmac", },
	{ .compatible = "amlogic,meson8b-rmii-dwmac", .data = &meson6_dwmac_data },// s805 chip 100m mode
	{ .compatible = "amlogic,meson6-rmii-dwmac",.data = &meson6_dwmac_data },// defined
#endif
	/* SoC specific glue layers should come before generic bindings */
	{ .compatible = "st,spear600-gmac"},
	{ .compatible = "snps,dwmac-3.610"},
	{ .compatible = "snps,dwmac-3.70a"},
	{ .compatible = "snps,dwmac-3.710"},
	{ .compatible = "snps,dwmac"},
	{ /* sentinel */ }
};
