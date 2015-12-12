#   ifndef GC_NO_THREADS_DISCOVERY
if (GC_win32_dll_threads) {
        int i;
        LONG my_max = GC_get_max_thread_index();

        for (i = 0; i <= my_max &&
                    (!AO_load_acquire(&dll_thread_table[i].tm.in_use)
                    || THREAD_EQUAL(dll_thread_table[i].pthread_id, id));
                    /* Must still be in_use, since nobody else can      */
                    /* store our thread_id.                             */
             i++) {
          /* empty */
        }
        return i <= my_max ? (GC_thread)(dll_thread_table + i) : NULL;
      } else
#   endif
    /* else */ {
      /* We first try the cache.  If that fails, we use a very slow     */
      /* approach.                                                      */
      word hv_guess = THREAD_TABLE_INDEX(GET_PTHREAD_MAP_CACHE(id));
      int hv;
      GC_thread p;
      DCL_LOCK_STATE;

      LOCK();
      for (p = GC_threads[hv_guess]; 0 != p; p = p -> tm.next) {
        if (THREAD_EQUAL(p -> pthread_id, id))
          goto foundit;
      }
      for (hv = 0; hv < THREAD_TABLE_SZ; ++hv) {
        for (p = GC_threads[hv]; 0 != p; p = p -> tm.next) {
          if (THREAD_EQUAL(p -> pthread_id, id))
            goto foundit;
        }
      }
      p = 0;
     foundit:
      UNLOCK();
      return p;
    }
