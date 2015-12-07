#ifdef HAVE_PARTITION
if (DB_IS_PARTITIONED(dbp)) {
		if ((ret = __partition_stat(dbc, &sp, flags)) != 0)
			return (ret);
	} else
#endif
	if ((ret = __bam_stat(dbc, &sp, LF_ISSET(DB_FAST_STAT))) != 0)
		return (ret);
