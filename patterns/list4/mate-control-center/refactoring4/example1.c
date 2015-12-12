#if GTK_CHECK_VERSION (3, 0, 0)
if (!cairo_region_contains_point (region, w, h))
#else
      if (!gdk_region_point_in (region, w, h))
#endif
      {
        p = pixels + h * rowstride + w * nchannels;
        if (G_BYTE_ORDER == G_BIG_ENDIAN)
          p[0] = 0x0;
        else
          p[3] = 0x0;
      }
