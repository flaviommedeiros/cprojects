if (!(ctype_encoding == encoding ||
		  ctype_encoding == PG_SQL_ASCII ||
		  ctype_encoding == -1 ||
#ifdef WIN32
		  encoding == PG_UTF8 ||
#endif
		  (encoding == PG_SQL_ASCII && superuser())))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("encoding \"%s\" does not match locale \"%s\"",
						pg_encoding_to_char(encoding),
						ctype),
		   errdetail("The chosen LC_CTYPE setting requires encoding \"%s\".",
					 pg_encoding_to_char(ctype_encoding))));
