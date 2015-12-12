if (category == LC_CTYPE
#ifdef LC_ALL
			|| category == LC_ALL
#endif
			)
		{
			char	   *newctype;

#ifdef LC_ALL
			if (category == LC_ALL)
				newctype = setlocale(LC_CTYPE, NULL);
			else
#endif
				newctype = RETVAL;
			new_ctype(newctype);
		}
