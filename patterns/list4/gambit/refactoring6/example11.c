if (avail > ___MSECTION_WASTE
#ifdef ___CALL_GC_FREQUENTLY
      && --___ps->mem.gc_calls_to_punt_ >= 0
#endif
     )
    {
      if (alloc_heap_ptr > alloc_heap_limit - ___MSECTION_FUDGE)
        next_heap_msection (___ps);

      prepare_mem_pstate (___ps);

      return 0;
    }
