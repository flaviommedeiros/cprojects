switch (input) {
			case 'h': case 'H': case '?':
			case KEY_F(1):
				show_help();
				break;
		case 'q': case 'Q':
			kill_work();
			return NULL;
		case 'd': case 'D':
			display_options();
			break;
		case 'm': case 'M':
			manage_device();
			break;
		case 'p': case 'P':
			display_pools();
			break;
		case 's': case 'S':
			set_options();
			break;
#ifdef HAVE_CURSES
		case KEY_DOWN:
		{
			const int visible_lines = logcursor - devcursor;
			const int invisible_lines = total_lines - visible_lines;
			if (devsummaryYOffset <= -invisible_lines)
				break;
			devsummaryYOffset -= 2;
		}
		case KEY_UP:
			if (devsummaryYOffset == 0)
				break;
			++devsummaryYOffset;
			refresh_devstatus();
			break;
		case KEY_NPAGE:
		{
			const int visible_lines = logcursor - devcursor;
			const int invisible_lines = total_lines - visible_lines;
			if (devsummaryYOffset - visible_lines <= -invisible_lines)
				devsummaryYOffset = -invisible_lines;
			else
				devsummaryYOffset -= visible_lines;
			refresh_devstatus();
			break;
		}
		case KEY_PPAGE:
		{
			const int visible_lines = logcursor - devcursor;
			if (devsummaryYOffset + visible_lines >= 0)
				devsummaryYOffset = 0;
			else
				devsummaryYOffset += visible_lines;
			refresh_devstatus();
			break;
		}
#endif
		}
