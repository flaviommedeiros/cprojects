if (LOGGING_ON(env)
#ifndef DEBUG_WOP
	    && txn != NULL
#endif
	) {
		/* Rename old to new. */
		DB_INIT_DBT(fid_dbt, olddbp->fileid, DB_FILE_ID_LEN);
		DB_INIT_DBT(n1_dbt, old, strlen(old) + 1);
		DB_INIT_DBT(n2_dbt, new, strlen(new) + 1);
		if ((ret = __crdel_inmem_rename_log(
		    env, txn, &lsn, 0, &n1_dbt, &n2_dbt, &fid_dbt)) != 0)
			goto err;

		/* Rename back to old */
		fid_dbt.data = backdbp->fileid;
		DB_SET_DBT(n2_dbt, back, strlen(back) + 1);
		if ((ret = __crdel_inmem_rename_log(
		    env, txn, &lsn, 0, &n2_dbt, &n1_dbt, &fid_dbt)) != 0)
			goto err;
	}
