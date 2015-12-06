#ifdef HAVE_CURSES
if (!use_curses || !input_pool(false))
#endif
			early_quit(1, "Pool setup failed");
