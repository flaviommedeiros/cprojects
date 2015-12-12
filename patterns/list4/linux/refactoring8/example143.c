static const struct gic_quirk its_quirks[] = {
#ifdef CONFIG_CAVIUM_ERRATUM_22375
	{
		.desc	= "ITS: Cavium errata 22375, 24313",
		.iidr	= 0xa100034c,	/* ThunderX pass 1.x */
		.mask	= 0xffff0fff,
		.init	= its_enable_quirk_cavium_22375,
	},
#endif
	{
	}
};
