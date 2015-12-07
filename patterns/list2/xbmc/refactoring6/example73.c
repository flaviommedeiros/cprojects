if ((ip = bank[bk]->tone[prog].instrument) == MAGIC_LOAD_INSTRUMENT
#ifndef SUPPRESS_CHANNEL_LAYER
			|| ip == NULL	/* see also readmidi.c: groom_list(). */
#endif
		) {ip = bank[bk]->tone[prog].instrument = load_instrument(dr, bk, prog);}
