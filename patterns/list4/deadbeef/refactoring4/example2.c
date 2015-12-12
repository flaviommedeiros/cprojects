#ifdef USE_GNOME
if (widget->parent
	  && (GTK_IS_FIXED (widget)
	      || (GTK_IS_LAYOUT (widget) && !GNOME_IS_CANVAS (widget))))
#else
      if (widget->parent
	  && (GTK_IS_FIXED (widget->parent)
	      || GTK_IS_LAYOUT (widget->parent)))
#endif
	{
	  pos = get_position_in_widget (widget, x, y);
	  switch (pos)
	    {
	    case GB_TOP_LEFT:
#if 0
	      g_print ("TOP_LEFT\n");
#endif
	      cursor = cursor_top_left;
	      break;
	    case GB_TOP_RIGHT:
#if 0
	      g_print ("TOP_RIGHT\n");
#endif
	      cursor = cursor_top_right;
	      break;
	    case GB_BOTTOM_LEFT:
#if 0
	      g_print ("BOTTOM_LEFT\n");
#endif
	      cursor = cursor_bottom_left;
	      break;
	    case GB_BOTTOM_RIGHT:
#if 0
	      g_print ("BOTTOM_RIGHT\n");
#endif
	      cursor = cursor_bottom_right;
	      break;
	    case GB_MIDDLE:
#if 0
	      g_print ("MIDDLE\n");
#endif
	      cursor = cursor_move;
	      break;
	    }
	}
      else
	{
	  cursor = cursor_selector;
	}
