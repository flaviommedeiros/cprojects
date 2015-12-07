#ifdef HAVE_FTRUNCATE
if (do_truncate) {
		start = (u_int32_t) (lp - list) + 1;
		meta->last_pgno--;
		ret = __db_truncate_freelist(
		      dbc, meta, h, list, start, nelem);
		h = NULL;
	} else
#endif
	if (h->pgno == last_pgno) {
		/*
		 * We are going to throw this page away, but if we are
		 * using MVCC then this version may stick around and we
		 * might have to make a copy.
		 */
		if (mpf->mfp->multiversion && (ret = __memp_dirty(mpf,
		    &h, dbc->thread_info, dbc->txn, dbc->priority, 0)) != 0)
			goto err1;
		LSN(h) = *lsnp;
		P_INIT(h, dbp->pgsize,
		    h->pgno, PGNO_INVALID, next_pgno, 0, P_INVALID);
		if ((ret = __memp_fput(mpf,
		    dbc->thread_info, h, DB_PRIORITY_VERY_LOW)) != 0)
			goto err1;
		h = NULL;
		/* Give the page back to the OS. */
		if ((ret = __memp_ftruncate(mpf, dbc->txn, dbc->thread_info,
		    last_pgno, 0)) != 0)
			goto err1;
		DB_ASSERT(dbp->env, meta->pgno == PGNO_BASE_MD);
		meta->last_pgno--;
		h = NULL;
	} else {
#ifdef HAVE_FTRUNCATE
		if (list != NULL) {
			/* Put the page number into the list. */
			if ((ret =
			    __memp_extend_freelist(mpf, nelem + 1, &list)) != 0)
				goto err1;
			if (prev_pgno != PGNO_INVALID)
				lp = &list[position + 1];
			else
				lp = list;
			if (nelem != 0 && position != nelem)
				memmove(lp + 1, lp, (size_t)
				    ((u_int8_t*)&list[nelem] - (u_int8_t*)lp));
			*lp = h->pgno;
		}
#endif
		/*
		 * If we are not truncating the page then we
		 * reinitialize it and put it at the head of
		 * the free list.
		 */
		if ((ret = __memp_dirty(mpf,
		    &h, dbc->thread_info, dbc->txn, dbc->priority, 0)) != 0)
			goto err1;
		LSN(h) = *lsnp;
		P_INIT(h, dbp->pgsize,
		    h->pgno, PGNO_INVALID, next_pgno, 0, P_INVALID);
#ifdef DIAGNOSTIC
		memset((u_int8_t *) h + P_OVERHEAD(dbp),
		    CLEAR_BYTE, dbp->pgsize - P_OVERHEAD(dbp));
#endif
		if (prev_pgno == PGNO_INVALID)
			meta->free = h->pgno;
		else
			NEXT_PGNO(prev) = h->pgno;
	}
