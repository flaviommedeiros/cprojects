#ifdef HAVE_X11_EXTENSIONS_XKB_H
if (strcmp (xkl_engine_get_backend_name (engine), "XKB"))
#endif
		gtk_widget_hide (WID ("xkb_layouts_print"));
