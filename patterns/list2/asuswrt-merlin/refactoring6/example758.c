if (DBENV_LOGGING(env) &&
#if !defined(DEBUG_WOP)
	    txn != NULL &&
#endif

	    (ret = __bam_root_log(mdbp, txn, &meta->dbmeta.lsn, 0,
	    meta->dbmeta.pgno, root->pgno, &meta->dbmeta.lsn)) != 0)
		goto err;
