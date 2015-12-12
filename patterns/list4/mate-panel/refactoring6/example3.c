if (effective_type == PANEL_BACK_IMAGE ||
	    (effective_type == PANEL_BACK_COLOR && background->has_alpha
#if GTK_CHECK_VERSION (3, 0, 0)
	    && (!gdk_window_check_composited_wm(background->window)))) {
		cairo_surface_t *surface;

		if (!background->composited_pattern)
			return NULL;
#else
	    )
