#if GTK_CHECK_VERSION (3, 0, 0)
if (background->window)
#else
	if (background->window && background->colormap && background->gc)
#endif
		return;
