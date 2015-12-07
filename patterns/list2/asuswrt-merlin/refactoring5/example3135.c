#ifdef HAVE_SHARED_LATCHES
if (F_ISSET(mutexp, DB_MUTEX_SHARED)) {
		sharecount = atomic_read(&mutexp->sharecount);
		/*MUTEX_MEMBAR(mutexp->sharecount);*/		/* XXX why? */
		if (sharecount == MUTEX_SHARE_ISEXCLUSIVE) {
			F_CLR(mutexp, DB_MUTEX_LOCKED);
			/* Flush flag update before zeroing count */
			MEMBAR_EXIT();
			atomic_init(&mutexp->sharecount, 0);
		} else {
			DB_ASSERT(env, sharecount > 0);
			MEMBAR_EXIT();
			sharecount = atomic_dec(env, &mutexp->sharecount);
			DB_ASSERT(env, sharecount >= 0);
			if (sharecount > 0)
				return (0);
		}
	} else
#endif
	{
		F_CLR(mutexp, DB_MUTEX_LOCKED);
		MUTEX_UNSET(&mutexp->tas);
	}
