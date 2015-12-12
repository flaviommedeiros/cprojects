switch(*b) {
#ifndef WANT_LEAD_0
		case '0':
			while(b[0] = b[1])
				b++;
			break;
#endif
		case 'i':
		case 'I':
			/* Infinity */
		case 'n':
		case 'N':
			/* NaN */
			while(*++b);
			break;

		default:
	/* Fortran 77 insists on having a decimal point... */
		    for(;; b++)
			switch(*b) {
			case 0:
				*b++ = '.';
				*b = 0;
				goto f__ret;
			case '.':
				while(*++b);
				goto f__ret;
			case 'E':
				for(c1 = '.', c = 'E';  *b = c1;
					c1 = c, c = *++b);
				goto f__ret;
			}
		}
