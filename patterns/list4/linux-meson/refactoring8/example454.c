static const struct of_device_id l2x0_ids[] __initconst = {
#ifdef CONFIG_PLAT_MESON
	{ .compatible = "arm,meson-pl310-cache", .data = (void *)&meson_pl310_data },
#endif
	{ .compatible = "arm,pl310-cache", .data = (void *)&pl310_data },
	{ .compatible = "arm,l220-cache", .data = (void *)&l2x0_data },
	{ .compatible = "arm,l210-cache", .data = (void *)&l2x0_data },
	{ .compatible = "marvell,aurora-system-cache",
	  .data = (void *)&aurora_no_outer_data},
	{ .compatible = "marvell,aurora-outer-cache",
	  .data = (void *)&aurora_with_outer_data},
	{}
};
