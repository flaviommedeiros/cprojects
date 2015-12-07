#ifdef G_OS_UNIX
if (debug_console)
		vte_terminal_copy_clipboard(debug_console);
	else
#endif
	{
     		g_signal_emit_by_name(debug_context, "copy-clipboard");
     	}
