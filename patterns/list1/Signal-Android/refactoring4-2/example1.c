#ifndef CHARSET_EBCDIC
while (	((ch >= 'A') && (ch <= 'Z')) ||
				((ch >= '0') && (ch <= '9')) ||
				((ch >= 'a') && (ch <= 'z')) ||
				 (ch == '-') || (ch == '.'))
#else
			while (	isalnum(ch) || (ch == '-') || (ch == '.'))
#endif
				 {
				 ch = *(++l);
				 buflen++;
				 }
