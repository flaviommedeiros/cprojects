static const struct dmi_system_id olpc_dmi_table[] __initconst = {
#if defined(CONFIG_DMI) && defined(CONFIG_OLPC)
	{
		/* OLPC XO-1 or XO-1.5 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "OLPC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "XO"),
		},
	},
#endif
	{ }
};
