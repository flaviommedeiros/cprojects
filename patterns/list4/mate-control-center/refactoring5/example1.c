#ifdef HAVE_X11_EXTENSIONS_XKB_H
if (!strcmp (xkl_engine_get_backend_name (engine), "XKB")) {
		kbdraw = xkb_layout_preview_create_widget (chooser_dialog);
		g_object_set_data (G_OBJECT (chooser), "kbdraw", kbdraw);
		gtk_container_add (GTK_CONTAINER
				   (CWID ("previewFrame")), kbdraw);
		gtk_widget_show_all (kbdraw);
		gtk_button_box_set_child_secondary (GTK_BUTTON_BOX
						    (CWID
						     ("hbtnBox")),
						    CWID
						    ("btnPrint"), TRUE);
	} else
#endif
	{
		gtk_widget_hide (CWID ("vboxPreview"));
		gtk_widget_hide (CWID ("btnPrint"));
	}
