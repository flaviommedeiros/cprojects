#if GTK_CHECK_VERSION (3, 0, 0)
if (!gdk_rgba_parse (&new_color, str_color))
#else
	if (!gdk_color_parse (str_color, &new_color))
#endif
		return;
