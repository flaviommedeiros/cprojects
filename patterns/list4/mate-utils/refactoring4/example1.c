#if GTK_CHECK_VERSION (3, 0, 0)
if (gdk_screen_is_composited (screen) &&
#if GTK_CHECK_VERSION (3, 0, 0)
      visual)
#else
      gdk_screen_get_rgba_colormap (screen)
