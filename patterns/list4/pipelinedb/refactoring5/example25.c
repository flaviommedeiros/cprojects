#ifdef HAVE_LOCALE_T
if (mylocale)
			{
				if (wasalnum)
					*p = tolower_l((unsigned char) *p, mylocale);
				else
					*p = toupper_l((unsigned char) *p, mylocale);
				wasalnum = isalnum_l((unsigned char) *p, mylocale);
			}
			else
#endif
			{
				if (wasalnum)
					*p = pg_tolower((unsigned char) *p);
				else
					*p = pg_toupper((unsigned char) *p);
				wasalnum = isalnum((unsigned char) *p);
			}
