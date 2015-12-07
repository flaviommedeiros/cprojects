#ifdef HAVE_SHARED_LATCHES
if (F_ISSET(mutexp, DB_MUTEX_SHARED))
		atomic_init(&mutexp->sharecount, 0);
	else
#endif
	if (MUTEX_INIT(&mutexp->tas)) {
		ret = __os_get_syserr();
		__db_syserr(env, ret, "TAS: mutex initialize");
		return (__os_posix_err(ret));
	}
