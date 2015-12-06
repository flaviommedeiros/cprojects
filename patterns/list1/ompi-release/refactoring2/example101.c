#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          MPI_Comm comm;
          uint32_t gid, wid;

          vt_win_id(win, &comm, &gid, &wid);

          if (was_recorded || env_mpi_ignore_filter)
            {
              vt_comment(tid, &time, "__RMASPECIALGROUP__");
              vt_mpi_rma_end(tid, &time, gid, wid);
            }

          vt_win_set_gid(win, VT_COMM_ID(comm));
        }
