if (parent_gbwidget
	  && parent_gbwidget->gb_widget_get_child_properties)
	(parent_gbwidget->gb_widget_get_child_properties) (widget->parent,
							   widget, data);
#ifdef USE_GNOME
      else if (BONOBO_IS_DOCK_ITEM (widget))
	{
	  gb_bonobo_dock_item_save_packing_properties (widget->parent, widget,
						       data);
	}
#endif
