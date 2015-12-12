if (background->has_alpha &&
#if GTK_CHECK_VERSION (3, 0, 0)
		    !gdk_window_check_composited_wm(background->window))
#else
		    background->composited_image
