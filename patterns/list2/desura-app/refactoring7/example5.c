return (/* LONG64_NPSetWindowCallbacStruct.type valid? */
		  (ws_info64->type == 0 || ws_info64->type == NP_SETWINDOW) &&
#ifdef MOZ_X11
		  /* LONG64_NPSetWindowCallbacStruct.display valid? */
		  is_browser_display(ws_info64->display) &&
#endif
		  1);
