switch (ch) {

#ifdef OS2
	case 224:	 /* function key prefix */
#endif /* OS2 */
	case '\0':
		return -1;

	case '\r':
	case '\n':
		return 1;

	case Ctrl('['):
		expanded = NONE;
		if (first_insert) {
			first_insert = 0;
			if (inslen == 0) {
				inslen = saved_inslen;
				return redo_insert(0);
			}
			lastcmd[0] = 'a';
			lastac = 1;
		}
		if (lastcmd[0] == 's' || lastcmd[0] == 'c' ||
				lastcmd[0] == 'C')
			return redo_insert(0);
		else
			return redo_insert(lastac - 1);

	/* { Begin nonstandard vi commands */
	case Ctrl('x'):
		expand_word(0);
		break;

	case Ctrl('f'):
		complete_word(0, 0);
		break;

	case Ctrl('e'):
		print_expansions(es, 0);
		break;

	case Ctrl('i'):
		if (Flag(FVITABCOMPLETE)) {
			complete_word(0, 0);
			break;
		}
		/* FALLTHROUGH */
	/* End nonstandard vi commands } */

	default:
		if (es->linelen >= es->cbufsize - 1)
			return -1;
		ibuf[inslen++] = ch;
		if (insert == INSERT) {
			memmove(&es->cbuf[es->cursor+1], &es->cbuf[es->cursor],
					es->linelen - es->cursor);
			es->linelen++;
		}
		es->cbuf[es->cursor++] = ch;
		if (insert == REPLACE && es->cursor > es->linelen)
			es->linelen++;
		expanded = NONE;
	}
