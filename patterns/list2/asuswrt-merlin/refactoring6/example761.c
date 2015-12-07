if (DBENV_LOGGING(env)
#if !defined(DEBUG_WOP)
	    && txn != NULL
#endif
	)
		if ((ret = __ham_groupalloc_log(mdbp, txn,
		    &LSN(mmeta), 0, &LSN(mmeta), meta->spares[0],
		    meta->max_bucket + 1, 0, mmeta->last_pgno)) != 0)
			goto err;
