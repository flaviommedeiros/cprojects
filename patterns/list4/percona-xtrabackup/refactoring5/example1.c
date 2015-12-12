#ifdef	KANJI
if ((*ch & 0200)) {
			el->el_state.metanext = 0;
			cmd = CcViMap[' '];
			break;
		} else
#endif /* KANJI */

		if (el->el_state.metanext) {
			el->el_state.metanext = 0;
			*ch |= 0200;
		}
