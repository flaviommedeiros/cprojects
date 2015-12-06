#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (dest != MPI_PROC_NULL && (was_recorded || env_mpi_ignore_filter))
            {
              VT_MPI_INT sz;
              PMPI_Type_size(datatype, &sz);
              vt_mpi_send(tid, &time, VT_RANK_TO_PE(dest, comm),
                          VT_COMM_ID(comm), tag, count * sz);
            }
        }
