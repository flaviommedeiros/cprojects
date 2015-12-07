#ifdef CE_ADAPTIVITY
if (nvram_match("reg_spec", "CE"))
		;
	else
#endif	/* CE_ADAPTIVITY */
	if (str && strlen(str))
//		fprintf(fp, "TxBurst=%d\n", atoi(str));
		fprintf(fp, "TxBurst=%d\n", strcmp(str, "off") ? 1 : 0);
	else
	{
		warning = 16;
		fprintf(fp, "TxBurst=%d\n", 1);
	}
