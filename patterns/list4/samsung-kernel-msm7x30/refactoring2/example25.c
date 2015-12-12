#ifdef CONFIG_DRM_LOAD_EDID_FIRMWARE
if (count == 0)
#endif
		count = (*connector_funcs->get_modes)(connector);
