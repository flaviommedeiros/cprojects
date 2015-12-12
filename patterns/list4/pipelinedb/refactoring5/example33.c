#ifdef LC_ALL
if (category == LC_ALL)
				newctype = setlocale(LC_CTYPE, NULL);
			else
#endif
				newctype = RETVAL;
