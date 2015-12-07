#ifdef HAVE_SHARED_LATCHES
if (F_ISSET(mutexp, DB_MUTEX_SHARED)) {
		if (F_ISSET(mutexp, DB_MUTEX_LOCKED)) {
			F_CLR(mutexp, DB_MUTEX_LOCKED);
			if ((ret = InterlockedExchange(
			    (interlocked_val)(&atomic_read(
			    &mutexp->sharecount)), 0)) !=
			    MUTEX_SHARE_ISEXCLUSIVE) {
				ret = DB_RUNRECOVERY;
				goto err;
			}
		} else if (InterlockedDecrement(
		    (interlocked_val)(&atomic_read(&mutexp->sharecount))) > 0)
			return (0);
	} else
#endif
	{
		F_CLR(mutexp, DB_MUTEX_LOCKED);
		MUTEX_UNSET(&mutexp->tas);
	}
