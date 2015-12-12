# ifndef GC_NO_THREADS_DISCOVERY
if (GC_win32_dll_threads) {
      /* This is intended to be lock-free.                              */
      /* It is either called synchronously from the thread being        */
      /* deleted, or by the joining thread.                             */
      /* In this branch asynchronous changes to (*t) are possible.      */
      /* It's not allowed to call GC_printf (and the friends) here,     */
      /* see GC_stop_world() for the information.                       */
      t -> stack_base = 0;
      t -> id = 0;
      AO_store_release(&t->tm.in_use, FALSE);
    } else
# endif
  /* else */ {
    DWORD id = ((GC_thread)t) -> id;
                /* Cast away volatile qualifier, since we have lock.    */
    word hv = THREAD_TABLE_INDEX(id);
    register GC_thread p = GC_threads[hv];
    register GC_thread prev = 0;

    GC_ASSERT(I_HOLD_LOCK());
    while (p != (GC_thread)t) {
      prev = p;
      p = p -> tm.next;
    }
    if (prev == 0) {
      GC_threads[hv] = p -> tm.next;
    } else {
      prev -> tm.next = p -> tm.next;
    }
  }
