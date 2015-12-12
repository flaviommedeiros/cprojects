#ifdef PCC_DEBUG_DBEX
if (_dbex) {
					unsigned char *cp = (unsigned char *)bp;
					unsigned short tmp;
					tmp = cp[1] << 8 | cp[0];
					writew(tmp, addr);
					bp++;
				} else
#endif
				writew(*bp++, addr);
