if (GTK_IS_WINDOW (widget)
	  || GTK_IS_DIALOG (widget)
	  || GTK_IS_COLOR_SELECTION_DIALOG (widget)
	  || GTK_IS_INPUT_DIALOG (widget)
	  || GTK_IS_FONT_SELECTION_DIALOG (widget)
	  || GTK_IS_FILE_SELECTION (widget)
#ifdef USE_GNOME
	  || GNOME_IS_APP (widget)
	  || GNOME_IS_DIALOG (widget)
#endif
	  )
	{
	  glade_util_show_message_box (_("You can't paste into windows or dialogs."), widget);
	  return;
	}
