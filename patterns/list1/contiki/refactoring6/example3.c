if(
#if CTK_CONF_WINDOWCLOSE
	      ev == ctk_signal_window_close &&
#endif /* CTK_CONF_WINDOWCLOSE */
	      data == (process_data_t)&window) {
      quit();
    } else if(ev == ctk_signal_widget_activate) {
      if((struct ctk_button *)data == &quitbutton) {
	quit();
      } else if((struct ctk_button *)data == &cancelbutton) {
#if CTK_CONF_WINDOWS
	ctk_dialog_close();
#else /* CTK_CONF_WINDOWS */
	ctk_window_close(&dialog);
	ctk_window_open(&window);
#endif /* CTK_CONF_WINDOWS */
	ptractive = 1;
      } else if((struct ctk_button *)data == &downloadbutton) {
#if CTK_CONF_WINDOWS
	ctk_dialog_close();
#else /* CTK_CONF_WINDOWS */
	ctk_window_close(&dialog);
	ctk_window_open(&window);
#endif /* CTK_CONF_WINDOWS */
	ptractive = 1;
	close_file();
	fd = cfs_open(localfilename, CFS_WRITE);
	if(fd != -1) {
	  show_statustext("Downloading ", remotefilename);
	  ftpc_get(connection, remotefilename);
	} else {
	  show_statustext("Could not create ", localfilename);
	}
      } else if((struct ctk_button *)data == &reloadbutton) {	
	start_loaddir();
#if CTK_CONF_WINDOWS
      } else if((struct ctk_button *)data == &connectionbutton) {
	ptractive = 0;
	make_connectionwindow();
	ctk_dialog_open(&connectionwindow);
      } else if((struct ctk_button *)data == &closebutton) {
	ctk_dialog_close();
	ptractive = 1;
#endif /* CTK_CONF_WINDOWS */
      } else if((struct ctk_button *)data == &anonymousbutton) {
	strcpy(username, "anonymous");
	strcpy(password, "contiki@ftp");
	CTK_WIDGET_REDRAW(&userentry);
	CTK_WIDGET_REDRAW(&passwordentry);
#if CTK_CONF_WINDOWS
      } else if((struct ctk_button *)data == &closeconnectionbutton) {
	ctk_dialog_close();
	ptractive = 1;
	ftpc_close(connection);
#endif /* CTK_CONF_WINDOWS */
      } else if((struct ctk_button *)data == &connectbutton) {
#if CTK_CONF_WINDOWS
	ctk_dialog_close();
#else /* CTK_CONF_WINDOWS */
	ctk_window_close(&connectionwindow);
	ctk_window_open(&window);
	showptr();
	start_loaddir();
#endif /* CTK_CONF_WINDOWS */
	ptractive = 1;
#if UIP_UDP
	if(uiplib_ipaddrconv(hostname, &ipaddr) == 0) {
	  if(resolv_lookup(hostname, &ipaddrptr) != RESOLV_STATUS_CACHED) {
	    resolv_query(hostname);
	    show_statustext("Resolving host ", hostname);
	    break;
	  }
	  connection = ftpc_connect(ipaddrptr, UIP_HTONS(21));
	  show_statustext("Connecting to ", hostname);
	} else {
	  connection = ftpc_connect(&ipaddr, UIP_HTONS(21));
	  show_statustext("Connecting to ", hostname);
	}
#else /* UIP_UDP */
	uiplib_ipaddrconv(hostname, &ipaddr);
	connection = ftpc_connect(&ipaddr, UIP_HTONS(21));
	show_statustext("Connecting to ", hostname);
#endif /* UIP_UDP */
      } 
      /*      if((struct ctk_button *)data == &closebutton) {
	ftpc_close(connection);
	}*/
    } else if(ptractive && ev == ctk_signal_keypress) {
      if((ctk_arch_key_t)(size_t)data == ' ') {
	if(ptrstate == PTRSTATE_LOCALFILES) {
	  ptrstate = PTRSTATE_REMOTEFILES;
	} else {
	  ptrstate = PTRSTATE_LOCALFILES;
	}
      } else if((ctk_arch_key_t)(size_t)data == CH_CURS_UP) {
	clearptr();
	if(ptrstate == PTRSTATE_LOCALFILES) {
	  if(localptr > 0) {
	    --localptr;
	  }
	} else {
	  if(remoteptr > 0) {
	    --remoteptr;
	  }
	}
      } else if((ctk_arch_key_t)(size_t)data == CH_CURS_DOWN) {
	clearptr();
	if(ptrstate == PTRSTATE_LOCALFILES) {
	  if(localptr < FILES_HEIGHT - 1) {
	    ++localptr;
	  }
	} else {
	  if(remoteptr < FILES_HEIGHT - 1) {
	    ++remoteptr;
	  }
	}
      } else if((ctk_arch_key_t)(size_t)data == CH_ENTER) {	
	if(ptrstate == PTRSTATE_LOCALFILES) {
	  strncpy(localfilename,
		  &localfiles[localptr * FILES_WIDTH], FILES_WIDTH);
	  strncpy(remotefilename,
		  &localfiles[localptr * FILES_WIDTH], FILES_WIDTH);
	  ptractive = 0;
	  make_uploaddialog();
#if CTK_CONF_WINDOWS
	  ctk_dialog_open(&dialog);
#else /* CTK_CONF_WINDOWS */
	  ctk_window_close(&window);
	  ctk_window_open(&dialog);
#endif /* CTK_CONF_WINDOWS */
	} else {
	  strncpy(localfilename,
		  &remotefiles[remoteptr * FILES_WIDTH], FILES_WIDTH);
	  strncpy(remotefilename,
		  &remotefiles[remoteptr * FILES_WIDTH], FILES_WIDTH);
	  ftpc_cwd(connection, remotefilename);
	  /*	  make_downloaddialog();
		  ctk_dialog_open(&dialog);*/
	}
      } else if((ctk_arch_key_t)(size_t)data == 'u') {
	ftpc_cdup(connection);
      }
      
      if(ptractive) {
        showptr();
      }
    }
