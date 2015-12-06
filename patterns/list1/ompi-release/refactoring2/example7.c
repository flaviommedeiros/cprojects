#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          /* finalize communicator, request, and file management */
          vt_comm_finalize();
          vt_request_finalize();
#if defined (HAVE_MPI2_IO) && HAVE_MPI2_IO
          vt_mpifile_finalize();
#endif /* HAVE_MPI2_IO */
        }
