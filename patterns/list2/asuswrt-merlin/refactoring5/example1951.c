#ifdef  PCC_DEBUG_DBEX
if (_dbex) {
					unsigned char *cp = (unsigned char *)bp;
					unsigned short tmp;
					tmp = readw(addr);
					cp[0] = tmp & 0xff;
					cp[1] = (tmp >> 8) & 0xff;
					bp++;
				} else
#endif
				*bp++ = readw(addr);
