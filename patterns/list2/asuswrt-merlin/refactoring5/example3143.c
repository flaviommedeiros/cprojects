#ifdef HAVE_PARTITION
if (dbp != NULL && DB_IS_PARTITIONED(dbp))
		return (__part_testdocopy(dbp, name));
	else
#endif
		return (__db_testdocopy(env, name));
