#if GTK_CHECK_VERSION (3, 0, 0)
if (visual == gdk_window_get_visual(gdk_window_get_parent(window)))
#else
  else if (visual == gdk_drawable_get_visual(GDK_DRAWABLE(gdk_window_get_parent(window))))
#endif
    {
      /* Otherwise, if the visual matches the visual of the parent window, we
       * can use a parent-relative background and fake transparency. */
#if GTK_CHECK_VERSION (3, 0, 0)
      gdk_window_set_background_pattern (window, NULL);
#else
      gdk_window_set_back_pixmap (window, NULL, TRUE);
#endif

      child->parent_relative_bg = TRUE;
    }
  else
    {
      /* Nothing to do; the icon will sit on top of an ugly gray box */
      child->parent_relative_bg = FALSE;
    }
