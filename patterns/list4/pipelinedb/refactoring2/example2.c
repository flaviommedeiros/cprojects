#ifndef WIN32
if (pg_strcasecmp(ctype, "C") == 0 || pg_strcasecmp(ctype, "POSIX") == 0)
#endif
		if (encoding != PG_SQL_ASCII &&
			raw_pg_bind_textdomain_codeset(domainname, encoding))
			return encoding;
