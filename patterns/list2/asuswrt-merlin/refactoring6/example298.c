if ((ret = __ham_return_meta(dbc,
#ifdef HAVE_FTRUNCATE
		    0,
#else
		    DB_MPOOL_DIRTY,
#endif
		&meta)) != 0)
			goto err;
