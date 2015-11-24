#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
      {
        struct VTRequest* orig_req;
        VT_MPI_INT i;
        for (i = 0; i < count; i++)
          {
            orig_req = vt_saved_request_get(i);
            vt_check_request(tid, &time, orig_req, &(array_of_statuses[i]),
                             (was_recorded || env_mpi_ignore_filter));
          }
      }
