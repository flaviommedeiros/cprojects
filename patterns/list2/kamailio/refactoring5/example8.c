#ifdef DBG_QM_MALLOC
if ((f=qm_find_free(qm, size, &hash, &list_cntr))!=0){
#else
	if ((f=qm_find_free(qm, size, &hash))!=0){
#endif
		/* we found it!*/
		/*detach it from the free list*/
#ifdef DBG_QM_MALLOC
			qm_debug_frag(qm, f, file, line);
#endif
		qm_detach_free(qm, f);
		/*mark it as "busy"*/
		f->u.is_free=0;
		qm->free_hash[hash].no--;
		qm->ffrags--;
		/* we ignore split return */
#ifdef DBG_QM_MALLOC
		split_frag(qm, f, size, file, "fragm. from qm_malloc", line, mname);
#else
		split_frag(qm, f, size);
#endif
		qm->real_used+=f->size;
		qm->used+=f->size;
		if (qm->max_real_used<qm->real_used)
			qm->max_real_used=qm->real_used;
#ifdef DBG_QM_MALLOC
		f->file=file;
		f->func=func;
		f->mname=mname;
		f->line=line;
		f->check=ST_CHECK_PATTERN;
		/*  FRAG_END(f)->check1=END_CHECK_PATTERN1;
			FRAG_END(f)->check2=END_CHECK_PATTERN2;*/
		MDBG("qm_malloc(%p, %lu) returns address %p frag. %p (size=%lu) on %d"
				" -th hit\n",
			 qm, size, (char*)f+sizeof(struct qm_frag), f, f->size, list_cntr );
#endif
#ifdef MALLOC_STATS
		if(qm->type==MEM_TYPE_PKG) {
			sr_event_exec(SREV_PKG_UPDATE_STATS, 0);
		}
#endif
		return (char*)f+sizeof(struct qm_frag);
	}
	return 0;
}
