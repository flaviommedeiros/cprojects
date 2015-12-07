#ifdef CE_ADAPTIVITY
if (nvram_match("reg_spec", "CE"))
		;
	else
#endif	/* CE_ADAPTIVITY */
	if (str && strlen(str))
		fprintf(fp, "HT_RDG=%d\n", atoi(str));
	else
	{
		warning = 29;
		fprintf(fp, "HT_RDG=%d\n", 0);
	}
