#ifdef CONFIG_HVC_OPAL
if (firmware_has_feature(FW_FEATURE_OPAL))
		hvc_opal_init_early();
	else
#endif
		add_preferred_console("hvc", 0, NULL);
