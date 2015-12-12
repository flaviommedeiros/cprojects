switch (c) {
		case 'p': /* pointer */
			flags &= ~(FL_LONG | FL_SHORT);
			if (sizeof(char *) > sizeof(int))
				flags |= FL_LONG; /* hope it fits.. */
			/* aaahhh... */
		case 'd':
		case 'i':
		case 'o':
		case 'u':
		case 'x':
			flags |= FL_NUMBER;
			s = &numbuf[sizeof(numbuf)];
			lnum = POP_INT(flags, c == 'd', args);
			switch (c) {
			case 'd':
			case 'i':
				if (0 > (long) lnum)
					lnum = - (long) lnum, tmp = 1;
				else
					tmp = 0;
				/* aaahhhh..... */

			case 'u':
				do {
					*--s = lnum % 10 + '0';
					lnum /= 10;
				} while (lnum);

				if (c != 'u') {
					if (tmp)
						*--s = '-';
					else if (flags & FL_PLUS)
						*--s = '+';
					else if (flags & FL_BLANK)
						*--s = ' ';
				}
				break;

			case 'o':
				do {
					*--s = (lnum & 0x7) + '0';
					lnum >>= 3;
				} while (lnum);

				if ((flags & FL_HASH) && *s != '0')
					*--s = '0';
				break;

			case 'p':
			case 'x':
			    {
				const char *digits = (flags & FL_UPPER) ?
						  "0123456789ABCDEF"
						: "0123456789abcdef";
				do {
					*--s = digits[lnum & 0xf];
					lnum >>= 4;
				} while (lnum);

				if (flags & FL_HASH) {
					*--s = (flags & FL_UPPER) ? 'X' : 'x';
					*--s = '0';
				}
			    }
			}
			len = &numbuf[sizeof(numbuf)] - s;
			if (flags & FL_DOT) {
				if (precision > len) {
					field = precision;
					flags |= FL_ZERO;
				} else
					precision = len; /* no loss */
			}
			break;

#ifdef FP
		case 'e':
		case 'g':
		case 'f':
		    {
			char *p;

			/*
			 *	This could probably be done better,
			 *  but it seems to work.  Note that gcvt()
			 *  is not used, as you cannot tell it to
			 *  not strip the zeros.
			 */
			flags |= FL_NUMBER;
			if (!(flags & FL_DOT))
				precision = 6;	/* default */
			/*
			 *	Assumes doubles are pushed on
			 *  the stack.  If this is not so, then
			 *  FL_LONG/FL_SHORT should be checked.
			 */
			fpnum = va_arg(args, double);
			s = fpbuf;
			style = c;
			/*
			 *  This is the same as
			 *	expo = ceil(log10(fpnum))
			 *  but doesn't need -lm.  This is an
			 *  approximation as expo is rounded up.
			 */
			(void) frexp(fpnum, &expo);
			expo = my_ceil(expo / LOG2_10);

			if (expo < 0)
				expo = 0;

			p = ecvt(fpnum, precision + 1 + expo,
				 &decpt, &tmp);
			if (c == 'g') {
				if (decpt < -4 || decpt > precision)
					style = 'e';
				else
					style = 'f';
				if (decpt > 0 && (precision -= decpt) < 0)
					precision = 0;
			}
			if (tmp)
				*s++ = '-';
			else if (flags & FL_PLUS)
				*s++ = '+';
			else if (flags & FL_BLANK)
				*s++ = ' ';

			if (style == 'e')
				*s++ = *p++;
			else {
				if (decpt > 0) {
					/* Overflow check - should
					 * never have this problem.
					 */
					if (decpt >
						&fpbuf[sizeof(fpbuf)]
							- s - 8)
						decpt =
						 &fpbuf[sizeof(fpbuf)]
							- s - 8;
					(void) memcpy(s, p, decpt);
					s += decpt;
					p += decpt;
				} else
					*s++ = '0';
			}

			/* print the fraction? */
			if (precision > 0) {
				*s++ = '.';
				/* Overflow check - should
				 * never have this problem.
				 */
				if (precision > &fpbuf[sizeof(fpbuf)]
							- s - 7)
					precision =
						&fpbuf[sizeof(fpbuf)]
						- s - 7;
				for (tmp = decpt;  tmp++ < 0 &&
					    precision > 0 ; precision--)
					*s++ = '0';
				tmp = strlen(p);
				if (precision > tmp)
					precision = tmp;
				/* Overflow check - should
				 * never have this problem.
				 */
				if (precision > &fpbuf[sizeof(fpbuf)]
							- s - 7)
					precision =
						&fpbuf[sizeof(fpbuf)]
						- s - 7;
				(void) memcpy(s, p, precision);
				s += precision;
				/*
				 *	`g' format strips trailing
				 *  zeros after the decimal.
				 */
				if (c == 'g' && !(flags & FL_HASH)) {
					while (*--s == '0')
						;
					if (*s != '.')
						s++;
				}
			} else if (flags & FL_HASH)
				*s++ = '.';

			if (style == 'e') {
				*s++ = (flags & FL_UPPER) ? 'E' : 'e';
				if (--decpt >= 0)
					*s++ = '+';
				else {
					*s++ = '-';
					decpt = -decpt;
				}
				p = &numbuf[sizeof(numbuf)];
				for (tmp = 0; tmp < 2 || decpt ; tmp++) {
					*--p = '0' + decpt % 10;
					decpt /= 10;
				}
				tmp = &numbuf[sizeof(numbuf)] - p;
				(void) memcpy(s, p, tmp);
				s += tmp;
			}

			len = s - fpbuf;
			s = fpbuf;
			precision = len;
			break;
		    }
#endif /* FP */

		case 's':
			if (!(s = va_arg(args, char *)))
				s = nulls;
			len = strlen(s);
			break;

		case 'c':
			flags &= ~FL_DOT;
			numbuf[0] = va_arg(args, int);
			s = numbuf;
			len = 1;
			break;

		case '%':
		default:
			numbuf[0] = c;
			s = numbuf;
			len = 1;
			break;
		}
