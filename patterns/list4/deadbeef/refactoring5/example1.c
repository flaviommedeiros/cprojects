#ifdef USE_GNOME
if (BONOBO_IS_DOCK_ITEM (widget))
    {
      gboolean is_floating;
      gint x, y;

      /* GnomeDockItem widgets which are floating automatically disappear when
	 the child is removed, so we remember the position and try to show it
	 again in the same place after adding the new widget. */
      is_floating = BONOBO_DOCK_ITEM (widget)->is_floating ? TRUE : FALSE;
      if (is_floating)
	bonobo_dock_item_get_floating_position (BONOBO_DOCK_ITEM (widget),
					       &x, &y);
      gtk_container_remove (GTK_CONTAINER (widget), current_child);
      gtk_widget_hide (new_child);
      gtk_container_add (GTK_CONTAINER (widget), new_child);
      gtk_widget_show (new_child);

      if (is_floating)
	bonobo_dock_item_detach (BONOBO_DOCK_ITEM (widget), x, y);
    }
  else if (GTK_IS_FRAME (widget))
#else
  if (GTK_IS_FRAME (widget))
#endif
    {
      /* If this is the frame's label widget, we replace that. */
      if (gtk_frame_get_label_widget (GTK_FRAME (widget)) == current_child)
	{
	  gtk_frame_set_label_widget (GTK_FRAME (widget), new_child);
	}
      else
	{
	  gtk_container_remove (GTK_CONTAINER (widget), current_child);
	  gtk_container_add (GTK_CONTAINER (widget), new_child);
	}
    }
  else if (GTK_IS_TOOL_ITEM (widget))
    {
      /* For a GtkToolItem, if the current child is a placeholder and the
	 GtkToolItem is not a GbWidget or the new child is a GtkToolItem,
	 we replace the GtkToolItem instead. Otherwise we replace the
	 placeholder as usual. */
      if (GB_IS_PLACEHOLDER (current_child)
	  && (!GB_IS_GB_WIDGET (widget) || GTK_IS_TOOL_ITEM (new_child)))
	{
	  return gb_widget_replace_child (widget->parent, widget, new_child);
	}
      else
	{
	  gtk_container_remove (GTK_CONTAINER (widget), current_child);
	  gtk_container_add (GTK_CONTAINER (widget), new_child);
	}
    }
  else if (GTK_IS_EXPANDER (widget))
    {
      /* If this is the expander's label widget, we replace that. */
      if (gtk_expander_get_label_widget (GTK_EXPANDER (widget)) == current_child)
	{
	  gtk_expander_set_label_widget (GTK_EXPANDER (widget), new_child);
	}
      else
	{
	  gtk_container_remove (GTK_CONTAINER (widget), current_child);
	  gtk_container_add (GTK_CONTAINER (widget), new_child);
	}
    }
  else if (GTK_IS_BIN (widget))
    {
      /* For a bin, we just delete the existing child and add the new one. */
      gtk_container_remove (GTK_CONTAINER (widget), current_child);
      gtk_container_add (GTK_CONTAINER (widget), new_child);
    }
  else if (GTK_IS_BOX (widget))
    {
      /* For a box, we find out the position of the current child, delete it,
         add the new one, and move it into position with reorder_child().
	 If the existing child is a placeholder and the new one is a menubar
	 or toolbar, we set the packing so it doesn't expand, as that is
	 probably what the user wants. */
      gboolean expand, fill;
      guint padding;
      GtkPackType pack_type;
      gint pos = glade_util_get_box_pos (GTK_BOX (widget), current_child);
      g_return_val_if_fail (pos != -1, FALSE);
      gtk_box_query_child_packing (GTK_BOX (widget), current_child,
				   &expand, &fill, &padding, &pack_type);

      /* If we are replacing a placeholder (i.e. we are adding a new widget),
	 we try to set the expand & fill options to reasonable defaults. */
      if (GB_IS_PLACEHOLDER (current_child))
	{
	  if (GTK_IS_LABEL (new_child)
	      || GTK_IS_BUTTON (new_child)
	      || GTK_IS_OPTION_MENU (new_child)
	      || GTK_IS_PROGRESS (new_child)
	      || GTK_IS_PROGRESS_BAR (new_child)
	      || GTK_IS_MENU_BAR (new_child)
	      || GTK_IS_TOOLBAR (new_child)
	      || GTK_IS_STATUSBAR (new_child))
	    {
	      expand = FALSE;
	      fill = FALSE;
	    }

	  /* In a vbox, entry & combo widgets should not expand/fill either. */
	  if (GTK_IS_VBOX (widget))
	    {
	      if (GTK_IS_ENTRY (new_child)
		  || GTK_IS_COMBO (new_child)
		  || GTK_IS_SPIN_BUTTON (new_child)
#ifdef USE_GNOME
		   || GNOME_IS_DATE_EDIT (new_child)
		   || GNOME_IS_FILE_ENTRY (new_child)
		   || GNOME_IS_PIXMAP_ENTRY (new_child)
#endif
		  )
		{
		  expand = FALSE;
		  fill = FALSE;
		}
	    }
	}

      gtk_container_remove (GTK_CONTAINER (widget), current_child);
      gtk_container_add (GTK_CONTAINER (widget), new_child);

      gtk_box_set_child_packing (GTK_BOX (widget), new_child, expand, fill,
				 padding, pack_type);
      gtk_box_reorder_child (GTK_BOX (widget), new_child, pos);

    }
  else if (GTK_IS_TOOLBAR (widget))
    {
      gint pos;

      pos = gtk_toolbar_get_item_index (GTK_TOOLBAR (widget),
					GTK_TOOL_ITEM (current_child));
      g_return_val_if_fail (pos != -1, FALSE);

      /* FIXME: GTK+/GNOME 2 bug workaround - something keeps a ref to the
	 initial buttons added to a GnomeApp, which causes when they eventually
	 get destroyed later and we try to remove them from the tree. So we
	 remove them from the tree here. */
      tree_remove_widget (current_child);

      gtk_container_remove (GTK_CONTAINER (widget), current_child);

      /* If the new child is a GtkToolItem, we can simply add it at the old
	 position. */
      if (GTK_IS_TOOL_ITEM (new_child))
	{
	  gtk_toolbar_insert (GTK_TOOLBAR (widget),
			      GTK_TOOL_ITEM (new_child), pos);
	}
      /* If the new child is a placeholder, we need to insert a
	 GtkToolItem above it (but not a GbWidget). */
      else if (GB_IS_PLACEHOLDER (new_child))
	{
	  GtkWidget *toolitem = (GtkWidget*) gtk_tool_item_new ();
	  gtk_widget_show (toolitem);
	  gtk_container_add (GTK_CONTAINER (toolitem), new_child);
	  gtk_toolbar_insert (GTK_TOOLBAR (widget),
			      GTK_TOOL_ITEM (toolitem), pos);
	}
      /* If the new child is not a GtkToolItem, we need to insert a
	 GtkToolItem above it, but use a GbWidget so its properties can be
	 set as required. */
      else
	{
	  GtkWidget *toolitem = gb_widget_new ("GtkToolItem", NULL);
	  gtk_widget_show (toolitem);
	  gtk_container_add (GTK_CONTAINER (toolitem), new_child);
	  gtk_toolbar_insert (GTK_TOOLBAR (widget),
			      GTK_TOOL_ITEM (toolitem), pos);
	  tree_add_widget (toolitem);
	}
    }
  else if (GTK_IS_LIST (widget))
    {
      /* For a list, we find out the position of the current child, delete it,
         and add the new one at the same position. */
      gint pos = gtk_list_child_position (GTK_LIST (widget), current_child);
      GList glist =
      {NULL, NULL, NULL};
      glist.data = current_child;
      gtk_list_remove_items (GTK_LIST (widget), &glist);
      glist.data = new_child;
      gtk_list_insert_items (GTK_LIST (widget), &glist, pos);

    }
  else if (GTK_IS_NOTEBOOK (widget))
    {
      /* For a notebook, we find out the position of the current child, delete
         it, and add the new one at the same position. If the current_child is
         a notebook tab, just replace it. */
      GtkWidget *page, *tab_label;
      gint pos;

      pos = find_notebook_page (GTK_NOTEBOOK (widget), current_child,
				&page, &tab_label);
      g_return_val_if_fail (pos != -1, FALSE);

      if (page == current_child)
	{
	  gtk_widget_ref (tab_label);
	  gtk_notebook_remove_page (GTK_NOTEBOOK (widget), pos);
	  gtk_notebook_insert_page (GTK_NOTEBOOK (widget),
				    new_child, tab_label, pos);
	  gtk_notebook_set_current_page (GTK_NOTEBOOK (widget), pos);
	  gtk_widget_unref (tab_label);
	}
      else
	{
	  gtk_widget_ref (page);
	  gtk_notebook_remove_page (GTK_NOTEBOOK (widget), pos);
	  gtk_notebook_insert_page (GTK_NOTEBOOK (widget),
				    page, new_child, pos);
	  gtk_notebook_set_current_page (GTK_NOTEBOOK (widget), pos);
	  gtk_widget_unref (page);
	}

    }
  else if (GTK_IS_PANED (widget))
    {
      /* For paned, we find out the position of the current child, delete it,
         and add the new one at the same position. */
      gint pos = (GTK_PANED (widget)->child1 == current_child) ? 1 : 2;
      gtk_container_remove (GTK_CONTAINER (widget), current_child);
      if (pos == 1)
	gtk_paned_add1 (GTK_PANED (widget), new_child);
      else
	gtk_paned_add2 (GTK_PANED (widget), new_child);

    }
  else if (GTK_IS_TABLE (widget))
    {
      /* For a table, we find out the position & size of the current child,
         delete it, and add the new one in the same place. */
      gint left, right, top, bottom;
      GtkTableChild *tchild;
      GtkAttachOptions xoptions, yoptions;

      tchild = glade_util_find_table_child (GTK_TABLE (widget), current_child);
      g_return_val_if_fail (tchild != NULL, FALSE);

      left = tchild->left_attach;
      right = tchild->right_attach;
      top = tchild->top_attach;
      bottom = tchild->bottom_attach;

      xoptions = 0;
      if (tchild->xexpand)
	xoptions |= GTK_EXPAND;
      if (tchild->xshrink)
	xoptions |= GTK_SHRINK;
      if (tchild->xfill)
	xoptions |= GTK_FILL;

      yoptions = 0;
      if (tchild->yexpand)
	yoptions |= GTK_EXPAND;
      if (tchild->yshrink)
	yoptions |= GTK_SHRINK;
      if (tchild->yfill)
	yoptions |= GTK_FILL;

      /* If we are replacing a placeholder (i.e. we are adding a new widget),
	 we try to set the expand & fill options to reasonable defaults. */
      if (GB_IS_PLACEHOLDER (current_child))
	{
	  if (GTK_IS_LABEL (new_child)
	      || GTK_IS_BUTTON (new_child)
	      || GTK_IS_OPTION_MENU (new_child)
	      || GTK_IS_PROGRESS (new_child)
	      || GTK_IS_PROGRESS_BAR (new_child)
	      || GTK_IS_MENU_BAR (new_child)
	      || GTK_IS_TOOLBAR (new_child)
	      || GTK_IS_STATUSBAR (new_child))
	    {
	      xoptions = GTK_FILL;
	      yoptions = 0;
	    }
	  else if (GTK_IS_ENTRY (new_child)
		   || GTK_IS_COMBO (new_child)
		   || GTK_IS_SPIN_BUTTON (new_child)
#ifdef USE_GNOME
		   || GNOME_IS_DATE_EDIT (new_child)
		   || GNOME_IS_FILE_ENTRY (new_child)
		   || GNOME_IS_PIXMAP_ENTRY (new_child)
#endif
		   )
	    {
	      xoptions = GTK_EXPAND | GTK_FILL;
	      yoptions = 0;
	    }
	}

      gtk_container_remove (GTK_CONTAINER (widget), current_child);
      gtk_table_attach (GTK_TABLE (widget), new_child,
			left, right, top, bottom, xoptions, yoptions, 0, 0);

      /* Note that if we have just added a placeholder, but there is already
	 a widget at the same position in the table, the placeholder will be
	 destroyed immediately. Thus don't rely on the new widget still being
	 alive after calling gb_widget_replace_child(). */
      gb_table_update_placeholders (widget, -1, -1);
    }
#if GLADE_SUPPORTS_GTK_TREE
  else if (GTK_IS_TREE (widget))
    {
      /* For a tree, we find out the position of the current child, delete it,
         and add the new one at the same position. */
      gint pos = gtk_tree_child_position (GTK_TREE (widget), current_child);
      GList glist =
      {NULL, NULL, NULL};
      glist.data = current_child;
      gtk_tree_remove_items (GTK_TREE (widget), &glist);
      gtk_tree_insert (GTK_TREE (widget), new_child, pos);

    }
#endif
  else if (GTK_IS_CLIST (widget))
    {
      /* For a clist, we check if the widget is a column title and if it is
	 we replace it. */
	gint pos;
	GtkCList *clist;

	clist = GTK_CLIST(widget);

	for (pos = 0; pos < clist->columns; pos++)
	{
	    if (clist->column[pos].button == current_child)
	    {
		gtk_clist_set_column_widget(clist, pos, new_child);
 	    }
	}
    }
  else if (GTK_IS_FIXED (widget) || GTK_IS_LAYOUT (widget))
    {
      GladeWidgetData *wdata;
      gint x, y, w, h;

      /* For a fixed, we find the position and size of the existing child,
	 remove it, and add the new one in the same place. */
      wdata = gtk_object_get_data (GTK_OBJECT (current_child),
				   GB_WIDGET_DATA_KEY);
      g_return_val_if_fail (wdata != NULL, FALSE);

      gtk_container_child_get (GTK_CONTAINER (widget), current_child,
			       "x", &x,
			       "y", &y,
			       NULL);
      w = wdata->width;
      h = wdata->height;

      wdata = gtk_object_get_data (GTK_OBJECT (new_child), GB_WIDGET_DATA_KEY);
      g_return_val_if_fail (wdata != NULL, FALSE);
      wdata->flags |= GLADE_WIDTH_SET | GLADE_HEIGHT_SET;
      wdata->width = w;
      wdata->height = h;

      /* Reset the widget's uposition, just in case it gets added to a standard
	 container. I don't think we need this for GTK+ 2. */
      /*gtk_widget_set_uposition (current_child, -1, -1);*/

      /* FIXME: GTK+ 1.2.3 bug workaround. We need to ref the widget to stop
	 gtk_layout_remove() from issuing a warning. */
      gtk_widget_ref (current_child);
      gtk_container_remove (GTK_CONTAINER (widget), current_child);
      gtk_widget_unref (current_child);

      if (GTK_IS_FIXED (widget))
	{
	  gtk_fixed_put (GTK_FIXED (widget), new_child, x, y);
	  /*gtk_widget_set_uposition (new_child, x, y);*/
	}
      else
	{
	  gtk_layout_put (GTK_LAYOUT (widget), new_child, x, y);
	}
      gb_widget_set_usize (new_child, w, h);
    }

#ifdef USE_GNOME
  else if (BONOBO_IS_DOCK (widget))
    {
      /* For a GnomeDock, we call bonobo_dock_set_client_area (). It removes
	 the existing child automatically. */
      bonobo_dock_set_client_area (BONOBO_DOCK (widget), new_child);
    }

#endif

  else if (GTK_IS_CONTAINER (widget))
    {
      /* General code for container - has to remove all children and add back
         NOTE: this may not work for specialised containers.
         NOTE: need to ref widgets? */
      g_warning (_("replacing child of container - not implemented yet\n"));
      return FALSE;
    }
