#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (source != MPI_PROC_NULL && result == MPI_SUCCESS)
            {
              vt_mpi_recv(tid, &time, VT_RANK_TO_PE(status->MPI_SOURCE, comm),
                          VT_COMM_ID(comm), status->MPI_TAG, count * sz);
            }
        }
