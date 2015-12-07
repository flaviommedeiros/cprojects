#ifdef HAVE_PARTITION
if (ret == 0 && DB_IS_PARTITIONED(dbp))
		ret = __part_lsn_reset(dbp, ip);
	else
#endif
	if (ret == 0 && dbp->type == DB_QUEUE)
#ifdef HAVE_QUEUE
		ret = __qam_lsn_reset(dbp, ip);
