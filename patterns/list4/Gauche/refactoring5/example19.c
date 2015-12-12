#   ifdef ENABLE_DISCLAIM
if ((hhdr -> hb_flags & HAS_DISCLAIM) != 0) {
        result = GC_disclaim_and_reclaim(hbp, hhdr, sz, list, count);
      } else
#   endif
    /* else */ if (init || GC_debugging_started) {
      result = GC_reclaim_clear(hbp, hhdr, sz, list, count);
    } else {
      GC_ASSERT((hhdr)->hb_descr == 0 /* Pointer-free block */);
      result = GC_reclaim_uninit(hbp, hhdr, sz, list, count);
    }
