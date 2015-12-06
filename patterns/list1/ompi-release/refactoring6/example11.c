if (OMPI_SUCCESS != (ret = set_f(MPI_TAG_UB, mca_pml.pml_max_tag)) ||
        OMPI_SUCCESS != (ret = set_f(MPI_HOST, MPI_PROC_NULL)) ||
        OMPI_SUCCESS != (ret = set_f(MPI_IO, MPI_ANY_SOURCE)) ||
        OMPI_SUCCESS != (ret = set_f(MPI_WTIME_IS_GLOBAL, 0)) ||
        OMPI_SUCCESS != (ret = set_f(MPI_LASTUSEDCODE,
                                     ompi_mpi_errcode_lastused)) ||
#if 0
        /* JMS For when we implement IMPI */
        OMPI_SUCCESS != (ret = set(IMPI_CLIENT_SIZE,
                                   &attr_impi_client_size)) ||
        OMPI_SUCCESS != (ret = set(IMPI_CLIENT_COLOR,
                                   &attr_impi_client_color)) ||
        OMPI_SUCCESS != (ret = set(IMPI_HOST_SIZE,
                                   &attr_impi_host_size)) ||
        OMPI_SUCCESS != (ret = set(IMPI_HOST_COLOR,
                                   &attr_impi_host_color)) ||
#endif
        0) {
        return ret;
    }
