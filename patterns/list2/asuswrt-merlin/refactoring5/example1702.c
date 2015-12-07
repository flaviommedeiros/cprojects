#ifdef HAVE_PARTITION
if (DB_IS_PARTITIONED(dbp))
		ret = __part_compact(dbp, ip, txn, start, stop, dp, flags, end);
	else
#endif
	switch (dbp->type) {
	case DB_HASH:
		if (!LF_ISSET(DB_FREELIST_ONLY))
			goto err;
		/* FALLTHROUGH */
	case DB_BTREE:
	case DB_RECNO:
		ret = __bam_compact(dbp, ip, txn, start, stop, dp, flags, end);
		break;

	default:
err:		ret = __dbh_am_chk(dbp, DB_OK_BTREE);
		break;
	}
