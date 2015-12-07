#ifdef	HAVE_VXWORKS
if (!create_ok)
#else
	if (!create_ok || ret != ENOENT)
#endif
		goto err;
