#if GTK_CHECK_VERSION (3, 0, 0)
if (!monitor->surface)
#else
	if (!monitor->gdkpixmap)
#endif
	{
		g_warning ("couldn't get background pixmap\n");
		gdk_x11_display_ungrab (display);
		monitor->display_grabbed = FALSE;
		return;
	}
