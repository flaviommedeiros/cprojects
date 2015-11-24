int
__wt_page_in_func(WT_SESSION_IMPL *session, WT_REF *ref, uint32_t flags
#ifdef HAVE_DIAGNOSTIC
    , const char *file, int line
#endif
    )
{
	WT_DECL_RET;
	WT_PAGE *page;
	u_int sleep_cnt, wait_cnt;
	int busy, force_attempts, oldgen;

	for (force_attempts = oldgen = 0, wait_cnt = 0;;) {
		switch (ref->state) {
		case WT_REF_DISK:
		case WT_REF_DELETED:
			if (LF_ISSET(WT_READ_CACHE))
				return (WT_NOTFOUND);

			/*
			 * The page isn't in memory, attempt to read it.
			 * Make sure there is space in the cache.
			 */
			WT_RET(__wt_cache_full_check(session));
			WT_RET(__wt_cache_read(session, ref));
			oldgen = LF_ISSET(WT_READ_WONT_NEED) ||
			    F_ISSET(session, WT_SESSION_NO_CACHE);
			continue;
		case WT_REF_READING:
			if (LF_ISSET(WT_READ_CACHE))
				return (WT_NOTFOUND);
			if (LF_ISSET(WT_READ_NO_WAIT))
				return (WT_NOTFOUND);
			WT_STAT_FAST_CONN_INCR(session, page_read_blocked);
			break;
		case WT_REF_LOCKED:
			if (LF_ISSET(WT_READ_NO_WAIT))
				return (WT_NOTFOUND);
			WT_STAT_FAST_CONN_INCR(session, page_locked_blocked);
			break;
		case WT_REF_SPLIT:
			return (WT_RESTART);
		case WT_REF_MEM:
			/*
			 * The page is in memory.
			 *
			 * Get a hazard pointer if one is required. We cannot
			 * be evicting if no hazard pointer is required, we're
			 * done.
			 */
			if (F_ISSET(S2BT(session), WT_BTREE_IN_MEMORY))
				goto skip_evict;

			/*
			 * The expected reason we can't get a hazard pointer is
			 * because the page is being evicted, yield, try again.
			 */
#ifdef HAVE_DIAGNOSTIC
			WT_RET(
			    __wt_hazard_set(session, ref, &busy, file, line));
#else
			WT_RET(__wt_hazard_set(session, ref, &busy));
#endif
			if (busy) {
				WT_STAT_FAST_CONN_INCR(
				    session, page_busy_blocked);
				break;
			}

			/*
			 * If eviction is configured for this file, check to see
			 * if the page qualifies for forced eviction and update
			 * the page's generation number. If eviction isn't being
			 * done on this file, we're done.
			 */
			if (F_ISSET(S2BT(session), WT_BTREE_NO_EVICTION))
				goto skip_evict;

			/*
			 * Forcibly evict pages that are too big.
			 */
			page = ref->page;
			if (force_attempts < 10 &&
			    __evict_force_check(session, page, flags)) {
				++force_attempts;
				ret = __wt_page_release_evict(session, ref);
				/* If forced eviction fails, stall. */
				if (ret == EBUSY) {
					ret = 0;
					wait_cnt += 1000;
					WT_STAT_FAST_CONN_INCR(session,
					    page_forcible_evict_blocked);
					break;
				} else
					WT_RET(ret);

				/*
				 * The result of a successful forced eviction
				 * is a page-state transition (potentially to
				 * an in-memory page we can use, or a restart
				 * return for our caller), continue the outer
				 * page-acquisition loop.
				 */
				continue;
			}

			/*
			 * If we read the page and we are configured to not
			 * trash the cache, set the oldest read generation so
			 * the page is forcibly evicted as soon as possible.
			 *
			 * Otherwise, update the page's read generation.
			 */
			if (oldgen && page->read_gen == WT_READGEN_NOTSET)
				__wt_page_evict_soon(page);
			else if (!LF_ISSET(WT_READ_NO_GEN) &&
			    page->read_gen != WT_READGEN_OLDEST &&
			    page->read_gen < __wt_cache_read_gen(session))
				page->read_gen =
				    __wt_cache_read_gen_set(session);
skip_evict:
			/*
			 * Check if we need an autocommit transaction.
			 * Starting a transaction can trigger eviction, so skip
			 * it if eviction isn't permitted.
			 */
			return (LF_ISSET(WT_READ_NO_EVICT) ? 0 :
			    __wt_txn_autocommit_check(session));
		WT_ILLEGAL_VALUE(session);
		}

		/*
		 * We failed to get the page -- yield before retrying, and if
		 * we've yielded enough times, start sleeping so we don't burn
		 * CPU to no purpose.
		 */
		if (++wait_cnt < 1000)
			__wt_yield();
		else {
			sleep_cnt = WT_MIN(wait_cnt, 10000);
			wait_cnt *= 2;
			WT_STAT_FAST_CONN_INCRV(session, page_sleep, sleep_cnt);
			__wt_sleep(0, sleep_cnt);
		}
	}
}
