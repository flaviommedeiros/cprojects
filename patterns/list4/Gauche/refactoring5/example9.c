#   ifdef GC_PTHREADS
if ((me -> flags & DETACHED) == 0) {
        me -> flags |= FINISHED;
      } else
#   endif
    /* else */ {
      GC_delete_thread(thread_id);
    }
