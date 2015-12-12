#ifdef HAVE_LOCALE_T
if (mylocale)
				*p = tolower_l((unsigned char) *p, mylocale);
			else
#endif
				*p = pg_tolower((unsigned char) *p);
