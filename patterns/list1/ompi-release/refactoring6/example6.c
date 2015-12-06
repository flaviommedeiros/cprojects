if (NULL == f_status ||
#if OMPI_BUILD_FORTRAN_BINDINGS
            /* This section is #if'ed out if we are not building the
               fortran bindings because these macros check values
               against constants that only exist if the fortran
               bindings exist. */
            OMPI_IS_FORTRAN_STATUS_IGNORE(f_status) ||
            OMPI_IS_FORTRAN_STATUSES_IGNORE(f_status) ||
#endif
            NULL == c_status) {
            return OMPI_ERRHANDLER_INVOKE(MPI_COMM_WORLD,
                                          MPI_ERR_IN_STATUS, FUNC_NAME);
        }
