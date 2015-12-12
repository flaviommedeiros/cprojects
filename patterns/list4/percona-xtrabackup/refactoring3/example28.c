switch (t) {
	case CHTYPE_ASCIICTL:
		return 2; /* ^@ ^? etc. */
	case CHTYPE_TAB:
		return 1; /* Hmm, this really need to be handled outside! */
	case CHTYPE_NL:
		return 0; /* Should this be 1 instead? */
#ifdef WIDECHAR
	case CHTYPE_PRINT:
		return wcwidth(c);
	case CHTYPE_NONPRINT:
		if (c > 0xffff) /* prefer standard 4-byte display over 5-byte */
			return 8; /* \U+12345 */
		else
			return 7; /* \U+1234 */
#else
	case CHTYPE_PRINT:
		return 1;
	case CHTYPE_NONPRINT:
		return 4; /* \123 */
#endif
	default:
		return 0; /* should not happen */
	}
