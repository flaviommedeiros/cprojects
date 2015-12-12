if (info->xwindow == screen->no_focus_window ||
          info->xwindow == screen->flash_window ||
#ifdef HAVE_COMPOSITE_EXTENSIONS
          info->xwindow == screen->wm_cm_selection_window ||
#endif
          info->xwindow == screen->wm_sn_selection_window) {
        meta_verbose ("Not managing our own windows\n");
        continue;
      }
