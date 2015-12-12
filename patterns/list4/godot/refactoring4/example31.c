#ifndef CHARSET_EBCDIC
if (!(	((buf[j] >= '0') && (buf[j] <= '9')) ||
				((buf[j] >= 'a') && (buf[j] <= 'f')) ||
				((buf[j] >= 'A') && (buf[j] <= 'F'))))
#else
			/* This #ifdef is not strictly necessary, since
			 * the characters A...F a...f 0...9 are contiguous
			 * (yes, even in EBCDIC - but not the whole alphabet).
			 * Nevertheless, isxdigit() is faster.
			 */
			if (!isxdigit(buf[j]))
#endif
				{
				i=j;
				break;
				}
