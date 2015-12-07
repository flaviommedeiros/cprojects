if (DBENV_LOGGING(env) &&
#if !defined(DEBUG_WOP)
	    txn != NULL &&
#endif
	    name != NULL) {
		DB_INIT_DBT(name_dbt, name, strlen(name) + 1);
		memset(&fid_dbt, 0, sizeof(fid_dbt));
		fid_dbt.data = dbp->fileid;
		fid_dbt.size = DB_FILE_ID_LEN;
		lfid = dbp->log_filename == NULL ?
		    DB_LOGFILEID_INVALID : dbp->log_filename->id;
		if ((ret = __crdel_inmem_create_log(env, txn,
		    &lsn, 0, lfid, &name_dbt, &fid_dbt, dbp->pgsize)) != 0)
			goto err;
	}
