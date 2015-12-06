int
__wt_scr_alloc_func(WT_SESSION_IMPL *session, size_t size, WT_ITEM **scratchp
#ifdef HAVE_DIAGNOSTIC
    , const char *file, int line
#endif
    )
{
	WT_DECL_RET;
	WT_ITEM *buf, **p, **best, **slot;
	size_t allocated;
	u_int i;

	/* Don't risk the caller not catching the error. */
	*scratchp = NULL;

	/*
	 * Each WT_SESSION_IMPL has an array of scratch buffers available for
	 * use by any function.  We use WT_ITEM structures for scratch memory
	 * because we already have functions that do variable-length allocation
	 * on a WT_ITEM.  Scratch buffers are allocated only by a single thread
	 * of control, so no locking is necessary.
	 *
	 * Walk the array, looking for a buffer we can use.
	 */
	for (i = 0, best = slot = NULL,
	    p = session->scratch; i < session->scratch_alloc; ++i, ++p) {
		/* If we find an empty slot, remember it. */
		if ((buf = *p) == NULL) {
			if (slot == NULL)
				slot = p;
			continue;
		}

		if (F_ISSET(buf, WT_ITEM_INUSE))
			continue;

		/*
		 * If we find a buffer that's not in-use, check its size: we
		 * want the smallest buffer larger than the requested size,
		 * or the largest buffer if none are large enough.
		 */
		if (best == NULL ||
		    (buf->memsize <= size && buf->memsize > (*best)->memsize) ||
		    (buf->memsize >= size && buf->memsize < (*best)->memsize))
			best = p;

		/* If we find a perfect match, use it. */
		if ((*best)->memsize == size)
			break;
	}

	/*
	 * If we didn't find a free buffer, extend the array and use the first
	 * slot we allocated.
	 */
	if (best == NULL && slot == NULL) {
		allocated = session->scratch_alloc * sizeof(WT_ITEM *);
		WT_ERR(__wt_realloc(session, &allocated,
		    (session->scratch_alloc + 10) * sizeof(WT_ITEM *),
		    &session->scratch));
#ifdef HAVE_DIAGNOSTIC
		allocated = session->scratch_alloc * sizeof(WT_SCRATCH_TRACK);
		WT_ERR(__wt_realloc(session, &allocated,
		    (session->scratch_alloc + 10) * sizeof(WT_SCRATCH_TRACK),
		    &session->scratch_track));
#endif
		slot = session->scratch + session->scratch_alloc;
		session->scratch_alloc += 10;
	}

	/*
	 * If slot is non-NULL, we found an empty slot, try to allocate a
	 * buffer.
	 */
	if (best == NULL) {
		WT_ASSERT(session, slot != NULL);
		best = slot;

		WT_ERR(__wt_calloc_one(session, best));

		/* Scratch buffers must be aligned. */
		F_SET(*best, WT_ITEM_ALIGNED);
	}

	/* Grow the buffer as necessary and return. */
	session->scratch_cached -= (*best)->memsize;
	WT_ERR(__wt_buf_init(session, *best, size));
	F_SET(*best, WT_ITEM_INUSE);

#ifdef HAVE_DIAGNOSTIC
	session->scratch_track[best - session->scratch].file = file;
	session->scratch_track[best - session->scratch].line = line;
#endif

	*scratchp = *best;
	return (0);

err:	WT_RET_MSG(session, ret,
	    "session unable to allocate a scratch buffer");
}
