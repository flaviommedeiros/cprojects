if (panel_global_config_get_highlight_when_over () && 
#if GTK_CHECK_VERSION (3, 0, 0)
		   (state_flags & GTK_STATE_FLAG_PRELIGHT || gtk_widget_has_focus (widget)))
#else
		   (button->in_button || gtk_widget_has_focus (widget))
