#       ifndef GC_PTHREADS_PARAMARK
if (mark_mutex_event == (HANDLE)0 || builder_cv == (HANDLE)0
              || mark_cv == (HANDLE)0)
            ABORT("CreateEvent failed");
