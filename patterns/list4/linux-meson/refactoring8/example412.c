static const struct pinctrl_map mackerel_pinctrl_map[] = {
	/* SDHI0 */
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mobile_sdhi.0", "pfc-sh7372",
				  "sdhi0_data4", "sdhi0"),
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mobile_sdhi.0", "pfc-sh7372",
				  "sdhi0_ctrl", "sdhi0"),
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mobile_sdhi.0", "pfc-sh7372",
				  "sdhi0_wp", "sdhi0"),
	/* SDHI1 */
#if !IS_ENABLED(CONFIG_MMC_SH_MMCIF)
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mobile_sdhi.1", "pfc-sh7372",
				  "sdhi1_data4", "sdhi1"),
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mobile_sdhi.1", "pfc-sh7372",
				  "sdhi1_ctrl", "sdhi1"),
#else
	/* MMCIF */
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mmcif.0", "pfc-sh7372",
				  "mmc0_data8_0", "mmc0"),
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mmcif.0", "pfc-sh7372",
				  "mmc0_ctrl_0", "mmc0"),
#endif
	/* SDHI2 */
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mobile_sdhi.2", "pfc-sh7372",
				  "sdhi2_data4", "sdhi2"),
	PIN_MAP_MUX_GROUP_DEFAULT("sh_mobile_sdhi.2", "pfc-sh7372",
				  "sdhi2_ctrl", "sdhi2"),
};
