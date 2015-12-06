#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
if (!is_mpi_multithreaded)
#endif /* HAVE_MPI2_THREAD */
        {
          if (source != MPI_PROC_NULL && result == MPI_SUCCESS)
            {
              VT_MPI_INT sz;
              PMPI_Type_size(datatype, &sz);
              vt_request_create(*request, (ERF_RECV | ERF_IS_PERSISTENT),
                                tag, source, count * sz, datatype, comm);
            }
        }
