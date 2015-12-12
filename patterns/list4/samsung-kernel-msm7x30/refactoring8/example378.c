static struct camera_vreg_t apq_8064_back_cam_vreg[] = {
	{"cam1_vdig", REG_LDO, 1200000, 1200000, 105000},
	{"cam1_vio", REG_VS, 0, 0, 0},
	{"cam1_vana", REG_LDO, 2850000, 2850000, 85600},
#if defined(CONFIG_IMX111) || defined(CONFIG_IMX091)
	{"cam1_vaf", REG_LDO, 2800000, 2800000, 300000},
#else
	{"cam1_vaf", REG_LDO, 1800000, 1800000, 150000},
#endif
};
