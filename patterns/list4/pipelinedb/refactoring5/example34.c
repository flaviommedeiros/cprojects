#ifdef LC_ALL
if (category == LC_ALL)
				newcoll = setlocale(LC_COLLATE, NULL);
			else
#endif
				newcoll = RETVAL;
