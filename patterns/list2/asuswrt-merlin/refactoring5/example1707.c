#ifdef HAVE_QNX
if (LF_ISSET(DB_OSO_REGION))
		ret = __os_qnx_region_open(env, name, oflags, mode, &fhp);
	else
#endif
	ret = __os_openhandle(env, name, oflags, mode, &fhp);
