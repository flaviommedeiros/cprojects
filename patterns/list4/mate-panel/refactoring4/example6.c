#if GTK_CHECK_VERSION (3, 0, 0)
if (background->type == PANEL_BACK_IMAGE && !background->composited_pattern)
#else
	if (background->type == PANEL_BACK_IMAGE && !background->composited_image)
#endif
		retval = PANEL_BACK_NONE;
