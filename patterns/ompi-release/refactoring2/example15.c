#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (*newgroup != MPI_GROUP_NULL && *newgroup != MPI_GROUP_EMPTY)
            vt_group_create(*newgroup);
        }
