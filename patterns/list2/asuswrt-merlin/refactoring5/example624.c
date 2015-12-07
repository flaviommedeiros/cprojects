#ifdef HAVE_COMPRESSION
if (DB_IS_COMPRESSED(dbp)) {
			*funcp =
			     ((BTREE *)dbp->bt_internal)->compress_dup_compare;
		} else
#endif
			*funcp = dbp->dup_compare;
