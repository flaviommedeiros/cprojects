static struct feature_table_entry rackmac_features[] = {
	{ PMAC_FTR_SCC_ENABLE,		core99_scc_enable },
	{ PMAC_FTR_IDE_ENABLE,		core99_ide_enable },
	{ PMAC_FTR_IDE_RESET,		core99_ide_reset },
	{ PMAC_FTR_GMAC_ENABLE,		core99_gmac_enable },
	{ PMAC_FTR_GMAC_PHY_RESET,	core99_gmac_phy_reset },
	{ PMAC_FTR_USB_ENABLE,		core99_usb_enable },
	{ PMAC_FTR_1394_ENABLE,		core99_firewire_enable },
	{ PMAC_FTR_1394_CABLE_POWER,	core99_firewire_cable_power },
	{ PMAC_FTR_SLEEP_STATE,		core99_sleep_state },
#ifdef CONFIG_SMP
	{ PMAC_FTR_RESET_CPU,		core99_reset_cpu },
#endif /* CONFIG_SMP */
	{ PMAC_FTR_READ_GPIO,		core99_read_gpio },
	{ PMAC_FTR_WRITE_GPIO,		core99_write_gpio },
	{ 0, NULL }
};
