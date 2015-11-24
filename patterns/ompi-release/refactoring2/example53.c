#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (*flag)
            {
              vt_check_request(tid, &time, orig_req, status,
                               (was_recorded || env_mpi_ignore_filter));
            }
        }
