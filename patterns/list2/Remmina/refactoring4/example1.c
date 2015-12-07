#if FLOATING_TOOLBAR_WIDGET
if (priv->floating_toolbar_widget)
#else
	if (priv->floating_toolbar_window)
#endif
	{
		gtk_label_set_text(GTK_LABEL(priv->floating_toolbar_label),
		                   remmina_file_get_string(cnnobj->remmina_file, "name"));
	}
