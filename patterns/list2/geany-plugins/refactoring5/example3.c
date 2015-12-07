#ifdef G_OS_UNIX
if (debug_console)
		vte_terminal_select_all(program_terminal);
	else
#endif
	{
		g_signal_emit_by_name(debug_context, "select-all");
	}
