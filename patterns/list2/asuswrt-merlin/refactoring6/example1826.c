if (DBENV_LOGGING(env) &&
#if !defined(DEBUG_WOP) && !defined(DIAGNOSTIC)
		    txn != NULL &&
#endif
		    dbp->log_filename != NULL)
			memcpy(dbp->log_filename->ufid,
			    dbp->fileid, DB_FILE_ID_LEN);
