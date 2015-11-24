if(mouse_moved
#if CTK_CONF_WINDOWS
		     && (window != &desktop_window || windows == NULL)
#endif /* CTK_CONF_WINDOWS */
		      ) {

		    process_post(window->owner, ctk_signal_pointer_move, NULL);

		    /* If there was a focused widget that is not below the
		       mouse pointer, we remove focus from the widget and
		       redraw it. */
		    if(window->focused != NULL &&
		       widget != window->focused) {
		      unfocus_widget(window->focused);
		    }
		    redraw |= REDRAW_WIDGETS;
		    if(widget != NULL) {
		      select_widget(widget);
		    }
		  }
