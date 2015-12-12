#ifdef CONFIG_DRM_LOAD_EDID_FIRMWARE
if (count == 0)
#endif
	{
		if (connector->override_edid) {
			struct edid *edid = (struct edid *) connector->edid_blob_ptr->data;

			count = drm_add_edid_modes(connector, edid);
		} else
			count = (*connector_funcs->get_modes)(connector);
	}
