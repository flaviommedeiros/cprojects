#ifdef G_OS_UNIX
if (pref_debug_console_vte)
	{
		console = vte_terminal_new();
		gtk_widget_show(console);
		debug_console = VTE_TERMINAL(console);
		dc_output = console_output;
		dc_output_nl = console_output_nl;
		g_signal_connect_after(debug_console, "realize", G_CALLBACK(on_vte_realize), NULL);
		menu_connect("console_menu", &console_menu_info, console);
	}
	else
#endif  /* G_OS_UNIX */
	{
		static const char *const colors[NFD] = { "#00C0C0", "#C0C0C0", "#C00000",
			"#C0C0C0", "#C000C0" };
		guint i;

		console = get_widget("debug_context");
		context_apply_config(console);
		debug_context = GTK_TEXT_VIEW(console);
		dc_output = context_output;
		dc_output_nl = context_output_nl;
		context = gtk_text_view_get_buffer(debug_context);

		for (i = 0; i < NFD; i++)
		{
			fd_tags[i] = gtk_text_buffer_create_tag(context, NULL, "foreground",
				colors[i], NULL);
		}
		g_signal_connect(console, "button-press-event",
			G_CALLBACK(on_console_button_3_press),
			menu_connect("console_menu", &console_menu_info, NULL));
	}
