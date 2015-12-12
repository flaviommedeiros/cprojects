static struct feature_table_entry g5_features[] = {
	{ PMAC_FTR_GMAC_ENABLE,		g5_gmac_enable },
	{ PMAC_FTR_1394_ENABLE,		g5_fw_enable },
	{ PMAC_FTR_ENABLE_MPIC,		g5_mpic_enable },
	{ PMAC_FTR_GMAC_PHY_RESET,	g5_eth_phy_reset },
	{ PMAC_FTR_SOUND_CHIP_ENABLE,	g5_i2s_enable },
#ifdef CONFIG_SMP
	{ PMAC_FTR_RESET_CPU,		g5_reset_cpu },
#endif /* CONFIG_SMP */
	{ PMAC_FTR_READ_GPIO,		core99_read_gpio },
	{ PMAC_FTR_WRITE_GPIO,		core99_write_gpio },
	{ 0, NULL }
};
