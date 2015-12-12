if (category == LC_NUMERIC
#ifdef LC_ALL
			|| category == LC_ALL
#endif
			)
		{
			char	   *newnum;

#ifdef LC_ALL
			if (category == LC_ALL)
				newnum = setlocale(LC_NUMERIC, NULL);
			else
#endif
				newnum = RETVAL;
			new_numeric(newnum);
		}
