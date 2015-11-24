if (!main_is_paused
#ifdef HAVE_MENU
         || menu_driver_alive()
#endif
         )
   {
      if (cmd.fullscreen_toggle)
         event_command(EVENT_CMD_FULLSCREEN_TOGGLE);
   }
