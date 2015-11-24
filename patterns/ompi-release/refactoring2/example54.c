#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (status == MPI_STATUS_IGNORE) status = &mystatus;
          vt_save_request_array(array_of_requests, count);
        }
