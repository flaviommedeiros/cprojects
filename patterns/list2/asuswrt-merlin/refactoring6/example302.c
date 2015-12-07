if ((ret = __fop_file_setup(dbp, ip,
			    txn, dname, mode, flags, &id)) == 0 &&
			    DBENV_LOGGING(env) && !F_ISSET(dbp, DB_AM_RECOVER)
#if !defined(DEBUG_ROP) && !defined(DEBUG_WOP) && !defined(DIAGNOSTIC)
			    && txn != NULL
#endif
#if !defined(DEBUG_ROP)
			    && !F_ISSET(dbp, DB_AM_RDONLY)
#endif
			)
				ret = __dbreg_log_id(dbp,
				    txn, dbp->log_filename->id, 1);
