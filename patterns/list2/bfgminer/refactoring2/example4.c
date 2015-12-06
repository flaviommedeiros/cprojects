#ifdef HAVE_CURSES
if (!use_curses || !input_pool(false))
#endif
			quit(1, "Pool setup failed");
