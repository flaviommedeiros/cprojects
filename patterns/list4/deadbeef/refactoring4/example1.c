#if 0
if (GTK_IS_FIXED (widget)
	       || (GTK_IS_LAYOUT (widget) && !GNOME_IS_CANVAS (widget)))
#else
      else if (GTK_IS_FIXED (widget) || GTK_IS_LAYOUT (widget))
#endif
	{
	  add_widget_to_fixed (widget, x, y);
#if 0
	  gtk_signal_emit_stop_by_name (GTK_OBJECT (signal_widget),
					"button_press_event");
#endif
	  return TRUE;
	}
      else if (GB_IS_PLACEHOLDER (widget))
	{
	  placeholder_replace (widget);
#if 0
	  gtk_signal_emit_stop_by_name (GTK_OBJECT (signal_widget),
					"button_press_event");
#endif
	  return TRUE;
	}
#if GLADE_SUPPORTS_GTK_PACKER
      else if (GTK_IS_PACKER (widget))
	{
	  add_widget_to_container (widget);
#if 0
	  gtk_signal_emit_stop_by_name (GTK_OBJECT (signal_widget),
					"button_press_event");
#endif
	  return TRUE;
	}
#endif
      else
        {
         static gboolean already_shown = FALSE;
         if (already_shown) 
           {
             /* Beep if user does mistake of invalid positioning from second
              * time.
              */
             gdk_beep ();	
           }
         else
           {
             glade_util_show_message_box (_("You can't add a widget at the selected position.\n"
					    "\n"
					    "Tip: GTK+ uses containers to lay out widgets.\n"
					    "Try deleting the existing widget and using\n"
					    "a box or table container instead.\n"), widget);
             already_shown = TRUE;
           }
        }
