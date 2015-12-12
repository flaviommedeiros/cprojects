struct msm_gpiomux_configs
msm8x60_surf_ffa_gpiomux_cfgs[] __initdata = {
	{msm8x60_gsbi_configs, ARRAY_SIZE(msm8x60_gsbi_configs)},
	{msm8x60_ebi2_configs, ARRAY_SIZE(msm8x60_ebi2_configs)},
	{msm8x60_uart_configs, ARRAY_SIZE(msm8x60_uart_configs)},
#if defined(CONFIG_USB_PEHCI_HCD) || defined(CONFIG_USB_PEHCI_HCD_MODULE)
	{msm8x60_isp_usb_configs, ARRAY_SIZE(msm8x60_isp_usb_configs)},
#endif
	{msm8x60_ts_configs, ARRAY_SIZE(msm8x60_ts_configs)},
	{msm8x60_aux_pcm_configs, ARRAY_SIZE(msm8x60_aux_pcm_configs)},
	{msm8x60_sdc_configs, ARRAY_SIZE(msm8x60_sdc_configs)},
	{msm8x60_snd_configs, ARRAY_SIZE(msm8x60_snd_configs)},
	{msm8x60_mi2s_configs, ARRAY_SIZE(msm8x60_mi2s_configs)},
	{msm8x60_lcdc_configs, ARRAY_SIZE(msm8x60_lcdc_configs)},
	{msm8x60_mdp_vsync_configs, ARRAY_SIZE(msm8x60_mdp_vsync_configs)},
	{msm8x60_hdmi_configs, ARRAY_SIZE(msm8x60_hdmi_configs)},
	{msm8x60_pmic_configs, ARRAY_SIZE(msm8x60_pmic_configs)},
	{msm8x60_common_configs, ARRAY_SIZE(msm8x60_common_configs)},
	{msm8x60_cam_configs, ARRAY_SIZE(msm8x60_cam_configs)},
	{msm8x60_tmg200_configs, ARRAY_SIZE(msm8x60_tmg200_configs)},
	{NULL, 0},
};
