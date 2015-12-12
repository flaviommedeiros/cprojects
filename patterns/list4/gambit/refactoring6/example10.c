if (avail > ___MSECTION_WASTE
#ifdef ___CALL_GC_FREQUENTLY
      && --___ps->mem.gc_calls_to_punt_ >= 0
#endif
     )
    {
      if (alloc_stack_ptr < alloc_stack_limit + ___MSECTION_FUDGE)
        {
          ___WORD frame;

          if (alloc_stack_ptr != ___ps->stack_break)
            frame = ___CAST(___WORD,alloc_stack_ptr);
          else
            frame = ___FP_STK(alloc_stack_ptr,-___BREAK_FRAME_NEXT);

          next_stack_msection (___ps);

          /*
           * Create a "break frame" in the new stack msection.
           */

          ___ps->stack_start = alloc_stack_start;
          alloc_stack_ptr = alloc_stack_start;

          ___FP_ADJFP(alloc_stack_ptr,___BREAK_FRAME_SPACE)
          ___FP_SET_STK(alloc_stack_ptr,-___BREAK_FRAME_NEXT,frame)

          ___ps->stack_break = alloc_stack_ptr;
        }

      prepare_mem_pstate (___ps);

      return 0;
    }
