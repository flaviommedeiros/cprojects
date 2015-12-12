#ifndef CHARSET_EBCDIC
if (	((*s == '/') &&
				((s[1] >= 'A') && (s[1] <= 'Z') && (
					(s[2] == '=') ||
					((s[2] >= 'A') && (s[2] <= 'Z') &&
					(s[3] == '='))
				 ))) ||
			(*s == '\0'))
#else
		if (	((*s == '/') &&
				(isupper(s[1]) && (
					(s[2] == '=') ||
					(isupper(s[2]) &&
					(s[3] == '='))
				 ))) ||
			(*s == '\0'))
#endif
			{
			i=s-c;
			if (BIO_write(bp,c,i) != i) goto err;
			c=s+1;	/* skip following slash */
			if (*s != '\0')
				{
				if (BIO_write(bp,", ",2) != 2) goto err;
				}
			l--;
			}
