if (!(locale_enc == user_enc ||
		  locale_enc == PG_SQL_ASCII ||
		  locale_enc == -1 ||
#ifdef WIN32
		  user_enc == PG_UTF8 ||
#endif
		  user_enc == PG_SQL_ASCII))
	{
		fprintf(stderr, _("%s: encoding mismatch\n"), progname);
		fprintf(stderr,
				_("The encoding you selected (%s) and the encoding that the\n"
			  "selected locale uses (%s) do not match.  This would lead to\n"
			"misbehavior in various character string processing functions.\n"
			   "Rerun %s and either do not specify an encoding explicitly,\n"
				  "or choose a matching combination.\n"),
				pg_encoding_to_char(user_enc),
				pg_encoding_to_char(locale_enc),
				progname);
		return false;
	}
