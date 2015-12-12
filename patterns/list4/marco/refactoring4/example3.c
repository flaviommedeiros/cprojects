#if GTK_CHECK_VERSION (3, 0, 0)
if (gdk_display_device_is_grabbed(gdk_display, device))
#else
	if (gdk_display_pointer_is_grabbed(gdk_display))
#endif
	{
		return FALSE;
	}
