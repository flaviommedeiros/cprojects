# ifndef GC_NO_THREADS_DISCOVERY
if (GC_win32_dll_threads) {
      int i;
      /* It appears to be unsafe to acquire a lock here, since this     */
      /* code is apparently not preemptible on some systems.            */
      /* (This is based on complaints, not on Microsoft's official      */
      /* documentation, which says this should perform "only simple     */
      /* initialization tasks".)                                        */
      /* Hence we make do with nonblocking synchronization.             */
      /* It has been claimed that DllMain is really only executed with  */
      /* a particular system lock held, and thus careful use of locking */
      /* around code that doesn't call back into the system libraries   */
      /* might be OK.  But this hasn't been tested across all win32     */
      /* variants.                                                      */
                  /* cast away volatile qualifier */
      for (i = 0;
           InterlockedExchange((void*)&dll_thread_table[i].tm.in_use, 1) != 0;
           i++) {
        /* Compare-and-swap would make this cleaner, but that's not     */
        /* supported before Windows 98 and NT 4.0.  In Windows 2000,    */
        /* InterlockedExchange is supposed to be replaced by            */
        /* InterlockedExchangePointer, but that's not really what I     */
        /* want here.                                                   */
        /* FIXME: We should eventually declare Win95 dead and use AO_   */
        /* primitives here.                                             */
        if (i == MAX_THREADS - 1)
          ABORT("Too many threads");
      }
      /* Update GC_max_thread_index if necessary.  The following is     */
      /* safe, and unlike CompareExchange-based solutions seems to work */
      /* on all Windows95 and later platforms.                          */
      /* Unfortunately, GC_max_thread_index may be temporarily out of   */
      /* bounds, so readers have to compensate.                         */
      while (i > GC_max_thread_index) {
        InterlockedIncrement((IE_t)&GC_max_thread_index);
      }
      if (GC_max_thread_index >= MAX_THREADS) {
        /* We overshot due to simultaneous increments.  */
        /* Setting it to MAX_THREADS-1 is always safe.  */
        GC_max_thread_index = MAX_THREADS - 1;
      }
      me = dll_thread_table + i;
    } else
# endif
  /* else */ /* Not using DllMain */ {
    GC_ASSERT(I_HOLD_LOCK());
    GC_in_thread_creation = TRUE; /* OK to collect from unknown thread. */
    me = GC_new_thread(thread_id);
    GC_in_thread_creation = FALSE;
    if (me == 0)
      ABORT("Failed to allocate memory for thread registering");
  }
