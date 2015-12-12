switch(GETC(ch)) {
		case EOF:
 eof:
			err(a->ciend,(EOF),where0);
		case '&':
		case '$':
			goto have_amp;
#ifndef No_Namelist_Questions
		case '?':
			print_ne(a);
			continue;
#endif
		default:
			if (ch <= ' ' && ch >= 0)
				continue;
#ifndef No_Namelist_Comments
			while(GETC(ch) != '\n')
				if (ch == EOF)
					goto eof;
#else
			errfl(a->cierr, 115, where0);
#endif
		}
