#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          PMPI_Type_size(datatype, &sz);
          if (dest != MPI_PROC_NULL && (was_recorded || env_mpi_ignore_filter))
            {
              vt_mpi_send(tid, &time, VT_RANK_TO_PE(dest, comm),
                          VT_COMM_ID(comm), sendtag, count * sz);
            }

          if (status == MPI_STATUS_IGNORE) status = &mystatus;
        }
