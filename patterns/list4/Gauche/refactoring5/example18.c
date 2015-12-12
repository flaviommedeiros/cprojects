#     ifdef CAN_CALL_ATFORK
if (pthread_atfork(fork_prepare_proc, fork_parent_proc,
                           fork_child_proc) == 0) {
          /* Handlers successfully registered.  */
          GC_handle_fork = 1;
        } else
#     endif
      /* else */ if (GC_handle_fork != -1)
        ABORT("pthread_atfork failed");
