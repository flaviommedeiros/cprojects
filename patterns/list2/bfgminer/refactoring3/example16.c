switch(w)
		{
			// NOTE: U+F000-U+F7FF are reserved for font hacks
			case '\0':
				return;
			case 0xb5:  // micro symbol
				w = unicode_micro;
				goto default_addch;
			case 0xf000:  // "bad" off
				wattroff(win, attr_bad);
				break;
			case 0xf001:  // "bad" on
				wattron(win, attr_bad);
				break;
#ifdef USE_UNICODE
			case '|':
				wadd_wch(win, WACS_VLINE);
				break;
#endif
			case 0x2500:  // BOX DRAWINGS LIGHT HORIZONTAL
			case 0x2534:  // BOX DRAWINGS LIGHT UP AND HORIZONTAL
				if (!use_unicode)
				{
					waddch(win, '-');
					break;
				}
#ifdef USE_UNICODE
				wadd_wch(win, (w == 0x2500) ? WACS_HLINE : WACS_BTEE);
				break;
#endif
			case 0x2022:
				if (w > WCHAR_MAX || !iswprint(w))
					w = '*';
			default:
default_addch:
				if (w > WCHAR_MAX || !(iswprint(w) || w == '\n'))
				{
#if REPLACEMENT_CHAR <= WCHAR_MAX
					if (iswprint(REPLACEMENT_CHAR))
						w = REPLACEMENT_CHAR;
					else
#endif
						w = '?';
				}
				{
#ifdef USE_UNICODE
					wchar_t wbuf[0x10];
					int wbuflen = sizeof(wbuf) / sizeof(*wbuf);
					wbuflen = swprintf(wbuf, wbuflen, L"%lc", (wint_t)w);
					waddnwstr(win, wbuf, wbuflen);
#else
					wprintw(win, "%lc", (wint_t)w);
#endif
				}
		}
