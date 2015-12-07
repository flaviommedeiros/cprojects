#ifdef G_OS_UNIX
if (debug_console)
		vte_terminal_reset(debug_console, TRUE, TRUE);
	else
#endif
	{
		gtk_text_buffer_set_text(context, "", -1);
		dc_chars = 0;
	}
