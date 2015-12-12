#ifdef USE_WIDE_UPPER_LOWER
if (GetDatabaseEncoding() == PG_UTF8)
		{
			if (pg_regex_locale)
				pg_regex_strategy = PG_REGEX_LOCALE_WIDE_L;
			else
				pg_regex_strategy = PG_REGEX_LOCALE_WIDE;
		}
		else
#endif   /* USE_WIDE_UPPER_LOWER */
		{
			if (pg_regex_locale)
				pg_regex_strategy = PG_REGEX_LOCALE_1BYTE_L;
			else
				pg_regex_strategy = PG_REGEX_LOCALE_1BYTE;
		}
