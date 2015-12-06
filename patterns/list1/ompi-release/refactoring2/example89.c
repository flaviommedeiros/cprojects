#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          vt_mpi_collend(tid, &time, matchid, &comm,
                         (was_recorded || env_mpi_ignore_filter));
        }
