# ifndef GC_NO_THREADS_DISCOVERY
if (GC_win32_dll_threads) {
      /* Unlike the other threads implementations, the thread table     */
      /* here contains no pointers to the collectible heap (note also   */
      /* that GC_PTHREADS is incompatible with DllMain-based thread     */
      /* registration).  Thus we have no private structures we need     */
      /* to preserve.                                                   */
    } else
# endif
  /* else */ {
    GC_push_all((ptr_t)(GC_threads), (ptr_t)(GC_threads)+sizeof(GC_threads));
  }
