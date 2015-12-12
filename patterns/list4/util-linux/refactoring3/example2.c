switch (key) {
		case KEY_RIGHT:
		case '\t':
			ui_menu_goto(cf, m->idx + 1);
			return 0;
		case KEY_LEFT:
#ifdef KEY_BTAB
		case KEY_BTAB:
#endif
			ui_menu_goto(cf, (int) m->idx - 1);
			return 0;
		}
