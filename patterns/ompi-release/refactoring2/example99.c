#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (was_recorded || env_mpi_ignore_filter)
            {
              MPI_Comm comm;
              uint32_t gid, wid;

              vt_win_id(win, &comm, &gid, &wid);
              vt_mpi_rma_end(tid, &time, gid, wid);
            }
        }
