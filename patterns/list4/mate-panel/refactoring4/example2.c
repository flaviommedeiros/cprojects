#if GTK_CHECK_VERSION (3, 0, 0)
if (!background->transformed)
#else
	if (!background->colormap || !background->transformed)
#endif
		return FALSE;
