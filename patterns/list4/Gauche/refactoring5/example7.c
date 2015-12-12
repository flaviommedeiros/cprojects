# ifndef GC_NO_THREADS_DISCOVERY
if (GC_win32_dll_threads) {
      int i;
      LONG my_max = GC_get_max_thread_index();
      for (i = 0; i <= my_max &&
                  (!AO_load_acquire(&dll_thread_table[i].tm.in_use)
                  || dll_thread_table[i].id != thread_id);
           /* Must still be in_use, since nobody else can store our     */
           /* thread_id.                                                */
           i++) {
        /* empty */
      }
      return i <= my_max ? (GC_thread)(dll_thread_table + i) : NULL;
    } else
# endif
  /* else */ {
    word hv = THREAD_TABLE_INDEX(thread_id);
    register GC_thread p = GC_threads[hv];

    GC_ASSERT(I_HOLD_LOCK());
    while (p != 0 && p -> id != thread_id) p = p -> tm.next;
    return(p);
  }
