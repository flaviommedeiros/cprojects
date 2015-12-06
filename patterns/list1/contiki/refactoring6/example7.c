if(ctk_arch_keyavail()
#if CTK_CONF_MOUSE_SUPPORT
	 || mouse_moved || mouse_button_changed
#endif /* CTK_CONF_MOUSE_SUPPORT */
	 ) {
	process_post(PROCESS_BROADCAST, ctk_signal_screensaver_stop, NULL);
	mode = CTK_MODE_NORMAL;
      }
