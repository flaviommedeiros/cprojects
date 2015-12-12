#if GTK_CHECK_VERSION (3, 0, 0)
if (gdk_rectangle_intersect (&rect, &pixbuf_rect, &dest))
#else
      GdkRectangle dest;
