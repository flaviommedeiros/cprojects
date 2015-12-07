#ifdef HAVE_COMPRESSION
if (DB_IS_COMPRESSED(dbp)) {
		dbp->dup_compare = __bam_compress_dupcmp;
		((BTREE *)dbp->bt_internal)->compress_dup_compare = func;
	} else
#endif
		dbp->dup_compare = func;
