if (DBENV_LOGGING(env)
#if !defined(DEBUG_WOP)
		    && txn != NULL
#endif
		) {
			memset(&fdbt, 0, sizeof(ndbt));
			fdbt.data = fileid;
			fdbt.size = fileid == NULL ? 0 : DB_FILE_ID_LEN;
			DB_INIT_DBT(ndbt, name, strlen(name) + 1);
			if ((ret = __fop_remove_log(env, txn, &lsn,
			    flags, &ndbt, &fdbt, (u_int32_t)appname)) != 0)
				goto err;
		}
