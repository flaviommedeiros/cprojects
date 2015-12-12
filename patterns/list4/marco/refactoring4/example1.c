#if GTK_CHECK_VERSION (3, 0, 0)
if (!gdk_rgba_parse (&spec->data.basic.color, str))
#else
      if (!gdk_color_parse (str, &spec->data.basic.color))
#endif
        {
          g_set_error (err, META_THEME_ERROR,
                       META_THEME_ERROR_FAILED,
                       _("Could not parse color \"%s\""),
                       str);
          meta_color_spec_free (spec);
          return NULL;
        }
