if (!settings->menu.pointer.enable
#ifdef HAVE_OVERLAY
       || (settings->input.overlay_enable && input_overlay_is_alive())
#endif
      )
      return 0;
