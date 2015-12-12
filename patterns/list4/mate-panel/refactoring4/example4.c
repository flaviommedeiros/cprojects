#if GTK_CHECK_VERSION (3, 0, 0)
if (gdk_rgba_equal (color, &background->color))
#else
	if (background->color.gdk.red   == color->gdk.red &&
	    background->color.gdk.green == color->gdk.green &&
	    background->color.gdk.blue  == color->gdk.blue &&
	    background->color.alpha  == color->alpha)
#endif
		return;
