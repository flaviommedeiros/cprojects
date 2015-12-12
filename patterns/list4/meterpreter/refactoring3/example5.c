switch (c) {
		case '%':
literal:
			if (fp->_r <= 0 && __srefill(fp))
				goto input_failure;
			if (*fp->_p != c)
				goto match_failure;
			fp->_r--, fp->_p++;
			nread++;
			continue;

		case '*':
			flags |= SUPPRESS;
			goto again;
		case 'j':
			flags |= MAXINT;
			goto again;
		case 'L':
			flags |= LONGDBL;
			goto again;
		case 'h':
			if (*fmt == 'h') {
				fmt++;
				flags |= SHORTSHORT;
			} else {
				flags |= SHORT;
			}
			goto again;
		case 'l':
			if (*fmt == 'l') {
				fmt++;
				flags |= LLONG;
			} else {
				flags |= LONG;
			}
			goto again;
		case 'q':
			flags |= LLONG;		/* deprecated */
			goto again;
		case 't':
			flags |= PTRINT;
			goto again;
		case 'z':
			flags |= SIZEINT;
			goto again;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			width = width * 10 + c - '0';
			goto again;

		/*
		 * Conversions.
		 * Those marked `compat' are for 4.[123]BSD compatibility.
		 *
		 * (According to ANSI, E and X formats are supposed
		 * to the same as e and x.  Sorry about that.)
		 */
		case 'D':	/* compat */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'd':
			c = CT_INT;
			base = 10;
			break;

		case 'i':
			c = CT_INT;
			base = 0;
			break;

		case 'O':	/* compat */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'o':
			c = CT_INT;
			flags |= UNSIGNED;
			base = 8;
			break;

		case 'u':
			c = CT_INT;
			flags |= UNSIGNED;
			base = 10;
			break;

		case 'X':
		case 'x':
			flags |= PFXOK;	/* enable 0x prefixing */
			c = CT_INT;
			flags |= UNSIGNED;
			base = 16;
			break;

#ifdef FLOATING_POINT
		case 'E':
		case 'G':
		case 'e': 
		case 'f': 
		case 'g':
			c = CT_FLOAT;
			break;
#endif

		case 's':
			c = CT_STRING;
			break;

		case '[':
			fmt = __sccl(ccltab, fmt);
			flags |= NOSKIP;
			c = CT_CCL;
			break;

		case 'c':
			flags |= NOSKIP;
			c = CT_CHAR;
			break;

		case 'p':	/* pointer format is like hex */
			flags |= POINTER | PFXOK;
			c = CT_INT;
			flags |= UNSIGNED;
			base = 16;
			break;

		case 'n':
			if (flags & SUPPRESS)
				continue;
			if (flags & SHORTSHORT)
				*va_arg(ap, __signed char *) = nread;
			else if (flags & SHORT)
				*va_arg(ap, short *) = nread;
			else if (flags & LONG)
				*va_arg(ap, long *) = nread;
			else if (flags & SIZEINT)
				*va_arg(ap, ssize_t *) = nread;
			else if (flags & PTRINT)
				*va_arg(ap, ptrdiff_t *) = nread;
			else if (flags & LLONG)
				*va_arg(ap, long long *) = nread;
			else if (flags & MAXINT)
				*va_arg(ap, intmax_t *) = nread;
			else
				*va_arg(ap, int *) = nread;
			continue;

		/*
		 * Disgusting backwards compatibility hacks.	XXX
		 */
		case '\0':	/* compat */
			return (EOF);

		default:	/* compat */
			if (isupper(c))
				flags |= LONG;
			c = CT_INT;
			base = 10;
			break;
		}
