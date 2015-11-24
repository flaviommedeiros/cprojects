#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (source != MPI_PROC_NULL && result == MPI_SUCCESS &&
              (was_recorded || env_mpi_ignore_filter))
            {
              VT_MPI_INT sz;
              PMPI_Type_size(recvtype, &sz);
              PMPI_Get_count(status, recvtype, &recvcount);
              if (recvcount == MPI_UNDEFINED)
                recvcount = 0;
              vt_mpi_recv(tid, &time, VT_RANK_TO_PE(status->MPI_SOURCE, comm),
                          VT_COMM_ID(comm), status->MPI_TAG,
                          recvcount * sz);
            }
        }
