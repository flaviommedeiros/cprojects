#ifdef HAVE_LOCALE_T
if (mylocale)
				*p = toupper_l((unsigned char) *p, mylocale);
			else
#endif
				*p = pg_toupper((unsigned char) *p);
