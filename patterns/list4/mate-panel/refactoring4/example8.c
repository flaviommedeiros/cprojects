#if GTK_CHECK_VERSION (3, 0, 0)
if (!fish->surface)
#else
	if (!fish->pixmap)
#endif
		update_pixmap (fish);
