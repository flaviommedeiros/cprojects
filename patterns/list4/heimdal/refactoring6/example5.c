if ((el->el_cursor.h & 0370) !=
					    (where & ~0x7)
#ifdef WIDECHAR
					    && (el->el_display[
					    el->el_cursor.v][where & 0370] !=
					    MB_FILL_CHAR)
#endif
					    ) {
						/* if not within tab stop */
						for (i =
						    (el->el_cursor.h & 0370);
						    i < (where & ~0x7);
						    i += 8)
							term__putc(el, '\t');
							/* then tab over */
						el->el_cursor.h = where & ~0x7;
					}
