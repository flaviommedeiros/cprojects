if (!settings->menu.mouse.enable
#ifdef HAVE_OVERLAY
       || (settings->input.overlay_enable && input_overlay_is_alive())
#endif
       )
   {
      menu_input->mouse.wheeldown = false;
      menu_input->mouse.wheelup   = false;
      menu_input->mouse.oldleft   = false;
      menu_input->mouse.oldright  = false;
      return 0;
   }
