#if __BYTE_ORDER == __LITTLE_ENDIAN
if ((fp = fopen(logFilePath, "a")))
#else
	if ((fp = fopen(logFilePath, "a")))
#endif
	{
		fprintf(fp, format);
		fclose(fp);
	}
