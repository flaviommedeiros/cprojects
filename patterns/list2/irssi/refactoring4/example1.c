#ifdef WIDEC_CURSES
if (get_wch(&key) == ERR)
#else
		if ((key = getch()) == ERR)
#endif
			break;
