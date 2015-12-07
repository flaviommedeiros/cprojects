#ifdef HAVE_PARTITION
if (DB_IS_PARTITIONED(dbp))
		ret = __partition_stat(dbc, spp, flags);
	else
#endif
	switch (dbp->type) {
	case DB_BTREE:
	case DB_RECNO:
		ret = __bam_stat(dbc, spp, flags);
		break;
	case DB_HASH:
		ret = __ham_stat(dbc, spp, flags);
		break;
	case DB_QUEUE:
		ret = __qam_stat(dbc, spp, flags);
		break;
	case DB_UNKNOWN:
	default:
		ret = (__db_unknown_type(env, "DB->stat", dbp->type));
		break;
	}
