#   ifndef CYGWIN32
if (GLOBAL_ALLOC_TEST)
#   endif
    {
      while (GC_n_heap_bases-- > 0) {
#       ifdef CYGWIN32
          /* FIXME: Is it OK to use non-GC free() here? */
#       else
          GlobalFree(GC_heap_bases[GC_n_heap_bases]);
#       endif
        GC_heap_bases[GC_n_heap_bases] = 0;
      }
    } /* else */
#   ifndef CYGWIN32
      else {
        /* Avoiding VirtualAlloc leak. */
        while (GC_n_heap_bases > 0) {
          VirtualFree(GC_heap_bases[--GC_n_heap_bases], 0, MEM_RELEASE);
          GC_heap_bases[GC_n_heap_bases] = 0;
        }
      }
