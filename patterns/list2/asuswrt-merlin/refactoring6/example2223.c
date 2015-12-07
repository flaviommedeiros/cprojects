if ((ret = __db_env_init(dbenv)) != 0 ||
	    (ret = __lock_env_create(dbenv)) != 0 ||
	    (ret = __log_env_create(dbenv)) != 0 ||
	    (ret = __memp_env_create(dbenv)) != 0 ||
#ifdef HAVE_REPLICATION
	    (ret = __rep_env_create(dbenv)) != 0 ||
#endif
	    (ret = __txn_env_create(dbenv)))
		goto err;
