if(
#if CTK_CONF_WINDOWCLOSE
	      ev == ctk_signal_window_close ||
#endif /* CTK_CONF_WINDOWCLOSE */
	      ev == PROCESS_EVENT_EXIT) {
      process_exit(&simpletelnet_process);
      ctk_window_close(&telnetwindow);
      LOADER_UNLOAD();
    } else if(ev == tcpip_event) {
      telnet_app(data);
    }
