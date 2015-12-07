#ifndef DIAG_MVCC
if (F_ISSET(env->dbenv, DB_ENV_MULTIVERSION))
#endif
		if (F_ISSET(dbp, DB_AM_TXN) &&
		    dbp->type != DB_QUEUE && dbp->type != DB_UNKNOWN)
			LF_SET(DB_MULTIVERSION);
