#if CTK_CONF_MENUS
if(menus.open == NULL)
#endif /* CTK_CONF_MENUS */
  {
#if CTK_CONF_WINDOWS
    window = widget->window;
    if(window == dialog) {
      ctk_draw_widget(widget, CTK_FOCUS_DIALOG, 0, height);
    } else if(dialog == NULL &&
	      (window == windows ||
	       window == &desktop_window))
#endif /* CTK_CONF_WINDOWS */
    {
      ctk_draw_widget(widget, CTK_FOCUS_WINDOW, 0, height);
    }
  }
