#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (*newintercomm != MPI_COMM_NULL)
            vt_comm_create(*newintercomm);
        }
