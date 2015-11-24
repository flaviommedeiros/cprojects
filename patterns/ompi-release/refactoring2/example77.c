#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          vt_mpi_collend(tid, &time, matchid, &comm,
                         (root != MPI_PROC_NULL && was_recorded));
        }
