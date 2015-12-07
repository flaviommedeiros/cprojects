#ifdef HAVE_COMPRESSION
if (DB_IS_COMPRESSED(dbp))
		ret = __bamc_compress_del(dbc, flags);
	else
#endif
		ret = __dbc_idel(dbc, flags);
