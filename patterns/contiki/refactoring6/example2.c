if(
#if CTK_CONF_WINDOWCLOSE
	      ev == ctk_signal_window_close ||
#endif
	      ev == PROCESS_EVENT_EXIT) {
      ctk_window_close(&tcpipwindow);
      netconf_quit();
    }
