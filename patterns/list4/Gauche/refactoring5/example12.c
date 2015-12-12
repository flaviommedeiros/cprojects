# ifndef GC_NO_THREADS_DISCOVERY
if (GC_win32_dll_threads) {
      int i;
      int my_max;
      /* Any threads being created during this loop will end up setting */
      /* GC_attached_thread when they start.  This will force marking   */
      /* to restart.  This is not ideal, but hopefully correct.         */
      AO_store(&GC_attached_thread, FALSE);
      my_max = (int)GC_get_max_thread_index();
      for (i = 0; i <= my_max; i++) {
        GC_vthread t = dll_thread_table + i;
        if (t -> stack_base != 0 && t -> thread_blocked_sp == NULL
            && t -> id != thread_id) {
          GC_suspend((GC_thread)t);
        }
      }
    } else
# endif
  /* else */ {
    GC_thread t;
    int i;

    for (i = 0; i < THREAD_TABLE_SZ; i++) {
      for (t = GC_threads[i]; t != 0; t = t -> tm.next) {
        if (t -> stack_base != 0 && t -> thread_blocked_sp == NULL
            && !KNOWN_FINISHED(t) && t -> id != thread_id) {
          GC_suspend(t);
        }
      }
    }
  }
