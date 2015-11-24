#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (array_of_statuses == MPI_STATUSES_IGNORE)
            array_of_statuses = get_status_array(count);
          vt_save_request_array(requests, count);
        }
