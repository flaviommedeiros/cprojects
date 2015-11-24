int
__wt_hazard_set(WT_SESSION_IMPL *session, WT_REF *ref, int *busyp
#ifdef HAVE_DIAGNOSTIC
    , const char *file, int line
#endif
    )
{
	WT_BTREE *btree;
	WT_CONNECTION_IMPL *conn;
	WT_HAZARD *hp;
	int restarts = 0;

	btree = S2BT(session);
	conn = S2C(session);
	*busyp = 0;

	/* If a file can never be evicted, hazard pointers aren't required. */
	if (F_ISSET(btree, WT_BTREE_IN_MEMORY))
		return (0);

	/*
	 * Do the dance:
	 *
	 * The memory location which makes a page "real" is the WT_REF's state
	 * of WT_REF_MEM, which can be set to WT_REF_LOCKED at any time by the
	 * page eviction server.
	 *
	 * Add the WT_REF reference to the session's hazard list and flush the
	 * write, then see if the page's state is still valid.  If so, we can
	 * use the page because the page eviction server will see our hazard
	 * pointer before it discards the page (the eviction server sets the
	 * state to WT_REF_LOCKED, then flushes memory and checks the hazard
	 * pointers).
	 *
	 * For sessions with many active hazard pointers, skip most of the
	 * active slots: there may be a free slot in there, but checking is
	 * expensive.  Most hazard pointers are released quickly: optimize
	 * for that case.
	 */
	for (hp = session->hazard + session->nhazard;; ++hp) {
		/*
		 * If we get to the end of the array, either:
		 * 1. If we know there are free slots somewhere, and this is
		 *    the first time through, continue the search from the
		 *    start.  Don't actually continue the loop because that
		 *    will skip the first slot.
		 * 2. If we have searched all the way through and we have
		 *    allocated the maximum number of slots, give up.
		 * 3. Allocate another increment of slots, up to the maximum.
		 *    The slot we are on should now be available.
		 */
		if (hp >= session->hazard + session->hazard_size) {
			if (session->nhazard < session->hazard_size &&
			    restarts++ == 0)
				hp = session->hazard;
			else if (session->hazard_size >= conn->hazard_max)
				break;
			else
				WT_PUBLISH(session->hazard_size, WT_MIN(
				    session->hazard_size + WT_HAZARD_INCR,
				    conn->hazard_max));
		}

		if (hp->page != NULL)
			continue;

		hp->page = ref->page;
#ifdef HAVE_DIAGNOSTIC
		hp->file = file;
		hp->line = line;
#endif
		/* Publish the hazard pointer before reading page's state. */
		WT_FULL_BARRIER();

		/*
		 * Check if the page state is still valid, where valid means a
		 * state of WT_REF_MEM and the pointer is unchanged.  (The
		 * pointer can change, it means the page was evicted between
		 * the time we set our hazard pointer and the publication.  It
		 * would theoretically be possible for the page to be evicted
		 * and a different page read into the same memory, so the
		 * pointer hasn't changed but the contents have.  That's OK, we
		 * found this page using the tree's key space, whatever page we
		 * find here is the page for us to use.)
		 */
		if (ref->page == hp->page && ref->state == WT_REF_MEM) {
			++session->nhazard;
			return (0);
		}

		/*
		 * The page isn't available, it's being considered for eviction
		 * (or being evicted, for all we know).  If the eviction server
		 * sees our hazard pointer before evicting the page, it will
		 * return the page to use, no harm done, if it doesn't, it will
		 * go ahead and complete the eviction.
		 *
		 * We don't bother publishing this update: the worst case is we
		 * prevent some random page from being evicted.
		 */
		hp->page = NULL;
		*busyp = 1;
		return (0);
	}

	__wt_errx(session, "session %p: hazard pointer table full", session);
#ifdef HAVE_DIAGNOSTIC
	__hazard_dump(session);
#endif

	return (ENOMEM);
}
