if (LOGGING_ON(env) && dbp->log_filename == NULL
#if !defined(DEBUG_ROP) && !defined(DEBUG_WOP) && !defined(DIAGNOSTIC)
	    && (txn != NULL || F_ISSET(dbp, DB_AM_RECOVER))
#endif
#if !defined(DEBUG_ROP)
	    && !F_ISSET(dbp, DB_AM_RDONLY)
#endif
	    ) {
		if ((ret = __dbreg_setup(dbp,
		    F_ISSET(dbp, DB_AM_INMEM) ? dname : fname,
		    F_ISSET(dbp, DB_AM_INMEM) ? NULL : dname, id)) != 0)
			return (ret);

		/*
		 * If we're actively logging and our caller isn't a
		 * recovery function that already did so, then assign
		 * this dbp a log fileid.
		 */
		if (DBENV_LOGGING(env) && !F_ISSET(dbp, DB_AM_RECOVER) &&
		    (ret = __dbreg_new_id(dbp, txn)) != 0)
			return (ret);
	}
