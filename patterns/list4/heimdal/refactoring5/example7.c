#ifdef WIDECHAR
if (*ch >= N_KEYS)
                        cmd = ED_INSERT;
		else
#endif
                        cmd = el->el_map.current[(unsigned char) *ch];
