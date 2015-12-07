#ifdef HAVE_LIBAVAHI_UI
if (setting->opt1)
	{
		gfe->priv->avahi_service_type = (const gchar*) setting->opt1;

		hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_widget_show(hbox);
		gtk_box_pack_start (GTK_BOX (hbox), widget, TRUE, TRUE, 0);

		widget = gtk_button_new_with_label ("...");
		s = g_strdup_printf(_("Browse the network to find a %s server"), plugin->name);
		gtk_widget_set_tooltip_text (widget, s);
		g_free(s);
		gtk_widget_show(widget);
		gtk_box_pack_start (GTK_BOX (hbox), widget, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(widget), "clicked", G_CALLBACK(remmina_file_editor_browse_avahi), gfe);

		gtk_grid_attach (GTK_GRID(grid), hbox, 1, row , 1, 1);
	}
	else
#endif
	{
		gtk_grid_attach(GTK_GRID(grid), widget, 1, row, 1, 1);
	}
