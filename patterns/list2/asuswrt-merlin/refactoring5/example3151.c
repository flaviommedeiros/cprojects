#ifdef HAVE_PARTITION
if (DB_IS_PARTITIONED(dbp))
		ret = __part_truncate(dbc, countp);
	else
#endif
	switch (dbp->type) {
	case DB_BTREE:
	case DB_RECNO:
		ret = __bam_truncate(dbc, countp);
		break;
	case DB_HASH:
		ret = __ham_truncate(dbc, countp);
		break;
	case DB_QUEUE:
		ret = __qam_truncate(dbc, countp);
		break;
	case DB_UNKNOWN:
	default:
		ret = __db_unknown_type(env, "DB->truncate", dbp->type);
		break;
	}
