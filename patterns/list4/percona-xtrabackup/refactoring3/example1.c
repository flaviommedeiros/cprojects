switch (p[1]) {
			case 'a':
				map = el->el_map.alt;
				break;

			case 's':
				ntype = XK_STR;
				break;
#ifdef notyet
			case 'c':
				ntype = XK_EXE;
				break;
#endif
			case 'k':
				key = 1;
				break;

			case 'r':
				rem = 1;
				break;

			case 'v':
				map_init_vi(el);
				return 0;

			case 'e':
				map_init_emacs(el);
				return 0;

			case 'l':
				ep = &el->el_map.help[el->el_map.nfunc];
				for (bp = el->el_map.help; bp < ep; bp++)
					(void) fprintf(el->el_outfile,
					    "" FSTR "\n\t" FSTR "\n",
					    bp->name, bp->description);
				return 0;
			default:
				(void) fprintf(el->el_errfile,
				    "" FSTR ": Invalid switch `%c'.\n",
                                               argv[0], (int) p[1]);
			}
