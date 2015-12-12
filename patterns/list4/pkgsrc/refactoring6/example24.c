if (state == SWORD
#ifdef KSH
		|| state == SLETPAREN
#endif /* KSH */
		)	/* ONEWORD? */
		return LWORD;
