if ((ret = __memp_fget(mpf, &pgno, dbc->thread_info, dbc->txn,
#ifdef HAVE_FTRUNCATE
		    0,
#else
		    DB_MPOOL_DIRTY,
#endif
		    &meta)) != 0)
			goto err1;
