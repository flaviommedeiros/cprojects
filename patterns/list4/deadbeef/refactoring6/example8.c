if (GTK_IS_FIXED (widget)
	  || GTK_IS_LAYOUT (widget)
#ifdef USE_GNOME
	  || BONOBO_IS_DOCK (widget)
#endif
	  )
	{
	  parent = widget;
	}
      else
	{
	  parent = widget->parent;
	  data.replacing_widget = widget;
	}
