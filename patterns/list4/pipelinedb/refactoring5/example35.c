#ifdef LC_ALL
if (category == LC_ALL)
				newnum = setlocale(LC_NUMERIC, NULL);
			else
#endif
				newnum = RETVAL;
