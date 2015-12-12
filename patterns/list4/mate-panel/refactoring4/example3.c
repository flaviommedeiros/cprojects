#if GTK_CHECK_VERSION (3, 0, 0)
if (background->color.alpha == (opacity / 65535.0))
#else
	if (background->color.alpha == opacity)
#endif
		return;
