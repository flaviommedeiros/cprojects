#ifdef alloca
if (powerbufLen < 3072)
		powerbufFree = alloca(powerbufLen+MOD_EXP_CTIME_MIN_CACHE_LINE_WIDTH);
	else
#endif
	if ((powerbufFree=(unsigned char*)OPENSSL_malloc(powerbufLen+MOD_EXP_CTIME_MIN_CACHE_LINE_WIDTH)) == NULL)
		goto err;
