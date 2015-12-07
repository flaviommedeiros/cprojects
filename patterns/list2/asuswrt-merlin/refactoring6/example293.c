if (DBENV_LOGGING(env)
#if !defined(DEBUG_WOP)
	    && txn != NULL
#endif
	    ) {
		DB_INIT_DBT(data, name, strlen(name) + 1);
		if (dirp != NULL && *dirp != NULL)
			DB_INIT_DBT(dirdata, *dirp, strlen(*dirp) + 1);
		else
			memset(&dirdata, 0, sizeof(dirdata));
		if ((ret = __fop_create_log(env, txn, &lsn,
		    flags | DB_FLUSH,
		    &data, &dirdata, (u_int32_t)appname, (u_int32_t)mode)) != 0)
			goto err;
	}
