#ifdef CONFIG_WAPI_SUPPORT
if (strcmp(param->u.crypt.alg, "SMS4"))
#endif
		{
		ret = -EINVAL;
		goto exit;
	}
