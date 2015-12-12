#   ifdef MSWIN32
if (GLOBAL_ALLOC_TEST) {
        /* VirtualAlloc doesn't like PAGE_EXECUTE_READWRITE.    */
        /* There are also unconfirmed rumors of other           */
        /* problems, so we dodge the issue.                     */
        result = (ptr_t) GlobalAlloc(0, bytes + HBLKSIZE);
        result = (ptr_t)(((word)result + HBLKSIZE - 1) & ~(HBLKSIZE-1));
      } else
#   endif
    /* else */ {
        /* VirtualProtect only works on regions returned by a   */
        /* single VirtualAlloc call.  Thus we allocate one      */
        /* extra page, which will prevent merging of blocks     */
        /* in separate regions, and eliminate any temptation    */
        /* to call VirtualProtect on a range spanning regions.  */
        /* This wastes a small amount of memory, and risks      */
        /* increased fragmentation.  But better alternatives    */
        /* would require effort.                                */
#       ifdef MPROTECT_VDB
          /* We can't check for GC_incremental here (because    */
          /* GC_enable_incremental() might be called some time  */
          /* later after the GC initialization).                */
#         ifdef GWW_VDB
#           define VIRTUAL_ALLOC_PAD (GC_GWW_AVAILABLE() ? 0 : 1)
#         else
#           define VIRTUAL_ALLOC_PAD 1
#         endif
#       else
#         define VIRTUAL_ALLOC_PAD 0
#       endif
        /* Pass the MEM_WRITE_WATCH only if GetWriteWatch-based */
        /* VDBs are enabled and the GetWriteWatch function is   */
        /* available.  Otherwise we waste resources or possibly */
        /* cause VirtualAlloc to fail (observed in Windows 2000 */
        /* SP2).                                                */
        result = (ptr_t) VirtualAlloc(NULL, bytes + VIRTUAL_ALLOC_PAD,
                                GetWriteWatch_alloc_flag
                                | (MEM_COMMIT | MEM_RESERVE)
                                | GC_mem_top_down,
                                GC_pages_executable ? PAGE_EXECUTE_READWRITE :
                                                      PAGE_READWRITE);
#       undef IGNORE_PAGES_EXECUTABLE
    }
