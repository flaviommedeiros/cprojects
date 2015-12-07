if (DBENV_LOGGING(env)
#if !defined(DEBUG_WOP)
	    && txn != NULL
#endif
	    ) {
		memset(&data, 0, sizeof(data));
		data.data = buf;
		data.size = size;
		DB_INIT_DBT(namedbt, name, strlen(name) + 1);
		if (dirname != NULL)
			DB_INIT_DBT(dirdbt, dirname, strlen(dirname) + 1);
		else
			memset(&dirdbt, 0, sizeof(dirdbt));
		if ((ret = __fop_write_log(env, txn,
		    &lsn, flags, &namedbt, &dirdbt, (u_int32_t)appname,
		    pgsize, pageno, off, &data, istmp)) != 0)
			goto err;
	}
