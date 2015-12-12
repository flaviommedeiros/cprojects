static inline void REGPARM(2) __small_free(void*_ptr,size_t _size) {
	__alloc_t* ptr=BLOCK_START(_ptr), *prev;
	size_t size=_size;
	size_t idx=get_index(size);
	
//	memset(ptr,0,size);	/* allways zero out small mem */
#if ALLOC_DEBUG >= ALLOC_DEBUG_ALL
	if (alloc_debug) printc("free (in %d): freeing %p of size %d and index %d.", 
				cos_spd_id(), ptr, size, idx);
#endif
	do {
		prev = __small_mem[idx];
		ptr->next=prev;
	} while (unlikely(cos_cmpxchg(&__small_mem[idx], (int)prev, (int)ptr) != (int)ptr));
	alloc_stats_report(DBG_FREE, idx);
}
