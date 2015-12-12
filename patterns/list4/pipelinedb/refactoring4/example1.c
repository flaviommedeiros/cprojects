#ifdef HAVE_INT64_TIMESTAMP
if (strcmp(tmpparam, "on") != 0)
#else
	if (strcmp(tmpparam, "off") != 0)
#endif
	{
		fprintf(stderr,
			 _("%s: integer_datetimes compile flag does not match server\n"),
				progname);
		PQfinish(tmpconn);
		exit(1);
	}
