if(dialog == NULL &&
#if CTK_CONF_MENUS
	    menus.open == NULL &&
#endif /* CTK_CONF_MENUS */
	    windows == w)
#endif /* CTK_CONF_WINDOWS */
  {
    ctk_draw_window(w, CTK_FOCUS_WINDOW, 0, height, 0);
  }
