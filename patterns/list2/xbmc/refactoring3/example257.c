switch (*arg) {
		case 'v':
			cmp->verbosity++;
			break;
		case 'q':
			cmp->verbosity--;
			break;
		case 't':	/* toggle */
			cmp->trace_playing = (cmp->trace_playing) ? 0 : 1;
			break;
		case 'l':
			cmp->flags ^= CTLF_LIST_LOOP;
			break;
		case 'r':
			cmp->flags ^= CTLF_LIST_RANDOM;
			break;
		case 's':
			cmp->flags ^= CTLF_LIST_SORT;
			break;
		case 'a':
			cmp->flags ^= CTLF_AUTOSTART;
			break;
		case 'x':
			cmp->flags ^= CTLF_AUTOEXIT;
			break;
		case 'd':
			cmp->flags ^= CTLF_DRAG_START;
			break;
		case 'u':
			cmp->flags ^= CTLF_AUTOUNIQ;
			break;
		case 'R':
			cmp->flags ^= CTLF_AUTOREFINE;
			break;
		case 'C':
			cmp->flags ^= CTLF_NOT_CONTINUE;
			break;
#ifdef IA_ALSASEQ
		case 'D':
			cmp->flags ^= CTLF_DAEMONIZE;
			break;
#endif
		default:
			ctl->cmsg(CMSG_ERROR, VERB_NORMAL,
					"Unknown interface option `%c'", *arg);
			return 1;
		}
