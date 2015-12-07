if (DBENV_LOGGING(env)
#if !defined(DEBUG_WOP)
	    && txn != NULL
#endif
	    ) {
		DB_INIT_DBT(old, oldname, strlen(oldname) + 1);
		DB_INIT_DBT(new, newname, strlen(newname) + 1);
		if (dirp != NULL && *dirp != NULL)
			DB_INIT_DBT(dir, *dirp, strlen(*dirp) + 1);
		else
			memset(&dir, 0, sizeof(dir));
		memset(&fiddbt, 0, sizeof(fiddbt));
		fiddbt.data = fid;
		fiddbt.size = DB_FILE_ID_LEN;
		if (with_undo)
			ret = __fop_rename_log(env,
			    txn, &lsn, flags | DB_FLUSH,
			    &old, &new, &dir, &fiddbt, (u_int32_t)appname);
		else
			ret = __fop_rename_noundo_log(env,
			    txn, &lsn, flags | DB_FLUSH,
			    &old, &new, &dir, &fiddbt, (u_int32_t)appname);
		if (ret != 0)
			goto err;
	}
