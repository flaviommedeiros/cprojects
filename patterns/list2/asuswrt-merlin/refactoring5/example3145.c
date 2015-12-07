#ifdef HAVE_PARTITION
if (DB_IS_PARTITIONED(dbp))
		ret = __partition_sync(dbp);
	else
#endif
	if (dbp->type == DB_QUEUE)
		ret = __qam_sync(dbp);
	else
		/* Flush any dirty pages from the cache to the backing file. */
		if ((t_ret = __memp_fsync(dbp->mpf)) != 0 && ret == 0)
			ret = t_ret;
