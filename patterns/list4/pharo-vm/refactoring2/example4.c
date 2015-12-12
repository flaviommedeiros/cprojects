#if defined(USE_XSHM)
if (!useXshm)
#endif
    {
      XPutImage(display, window, gc, image, src_x, src_y, dst_x, dst_y, w, h);
      return;
    }
