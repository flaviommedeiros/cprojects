# ifndef DARWIN_DONT_PARSE_STACK
if (GC_query_task_threads) {
      kern_return_t kern_result;
      thread_act_array_t act_list = 0;

      /* Obtain the list of the threads from the kernel.  */
      kern_result = task_threads(my_task, &act_list, &listcount);
      if (kern_result != KERN_SUCCESS)
        ABORT("task_threads failed");

      for (i = 0; i < (int)listcount; i++) {
        thread_act_t thread = act_list[i];
        lo = GC_stack_range_for(&hi, thread, NULL, FALSE, my_thread);
        GC_ASSERT((word)lo <= (word)hi);
        total_size += hi - lo;
        GC_push_all_stack(lo, hi);
        nthreads++;
        if (thread == my_thread)
          found_me = TRUE;
        mach_port_deallocate(my_task, thread);
      } /* for (i=0; ...) */

      vm_deallocate(my_task, (vm_address_t)act_list,
                    sizeof(thread_t) * listcount);
    } else
# endif /* !DARWIN_DONT_PARSE_STACK */
  /* else */ {
    for (i = 0; i < (int)listcount; i++) {
      GC_thread p;
      for (p = GC_threads[i]; p != NULL; p = p->next)
        if ((p->flags & FINISHED) == 0) {
          thread_act_t thread = (thread_act_t)p->stop_info.mach_thread;
          lo = GC_stack_range_for(&hi, thread, p, (GC_bool)p->thread_blocked,
                                  my_thread);
          GC_ASSERT((word)lo <= (word)hi);
          total_size += hi - lo;
          GC_push_all_stack_sections(lo, hi, p->traced_stack_sect);
          nthreads++;
          if (thread == my_thread)
            found_me = TRUE;
        }
    } /* for (i=0; ...) */
  }
