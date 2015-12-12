#   ifdef MSWINCE
if (GC_dont_query_stack_min) {
        stack_min = GC_wince_evaluate_stack_min(traced_stack_sect != NULL ?
                      (ptr_t)traced_stack_sect : thread -> stack_base);
        /* Keep last_stack_min value unmodified. */
      } else
#   endif
    /* else */ {
      stack_min = GC_get_stack_min(traced_stack_sect != NULL ?
                      (ptr_t)traced_stack_sect : thread -> stack_base);
      UNPROTECT_THREAD(thread);
      thread -> last_stack_min = stack_min;
    }
