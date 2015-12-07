#ifdef HAVE_HASH
if (hash) {
			if ((ret =
			    __ham_return_meta(dbc, DB_MPOOL_DIRTY, &meta)) != 0)
				goto err1;
		} else
#endif
		if ((ret = __memp_dirty(mpf,
		    &meta, dbc->thread_info, dbc->txn, dbc->priority, 0)) != 0)
			goto err1;
