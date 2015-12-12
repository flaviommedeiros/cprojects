# ifndef GC_NO_THREADS_DISCOVERY
if (GC_win32_dll_threads) {
      if (GC_please_stop) {
        AO_store(&GC_attached_thread, TRUE);
        AO_nop_full(); /* Later updates must become visible after this. */
      }
      /* We'd like to wait here, but can't, since waiting in DllMain    */
      /* provokes deadlocks.                                            */
      /* Thus we force marking to be restarted instead.                 */
    } else
# endif
  /* else */ {
    GC_ASSERT(!GC_please_stop);
        /* Otherwise both we and the thread stopping code would be      */
        /* holding the allocation lock.                                 */
  }
