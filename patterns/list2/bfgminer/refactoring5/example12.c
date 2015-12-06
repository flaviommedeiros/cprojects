#ifdef HAVE_CURSES
if (use_curses) {
				halfdelay(150);
				applog(LOG_ERR, "Press any key to exit, or BFGMiner will try again in 15s.");
				if (getch() != ERR)
					quit(0, "No servers could be used! Exiting.");
				cbreak();
			} else
#endif
				quit(0, "No servers could be used! Exiting.");
