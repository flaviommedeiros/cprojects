if (OMPI_SUCCESS != (ret = create_comm(MPI_TAG_UB, true)) ||
        OMPI_SUCCESS != (ret = create_comm(MPI_HOST, true)) ||
        OMPI_SUCCESS != (ret = create_comm(MPI_IO, true)) ||
        OMPI_SUCCESS != (ret = create_comm(MPI_WTIME_IS_GLOBAL, true)) ||
        OMPI_SUCCESS != (ret = create_comm(MPI_APPNUM, true)) ||
        OMPI_SUCCESS != (ret = create_comm(MPI_LASTUSEDCODE, false)) ||
        OMPI_SUCCESS != (ret = create_comm(MPI_UNIVERSE_SIZE, true)) ||
        OMPI_SUCCESS != (ret = create_win(MPI_WIN_BASE)) ||
        OMPI_SUCCESS != (ret = create_win(MPI_WIN_SIZE)) ||
        OMPI_SUCCESS != (ret = create_win(MPI_WIN_DISP_UNIT)) ||
        OMPI_SUCCESS != (ret = create_win(MPI_WIN_CREATE_FLAVOR)) ||
        OMPI_SUCCESS != (ret = create_win(MPI_WIN_MODEL)) ||
#if 0
        /* JMS For when we implement IMPI */
        OMPI_SUCCESS != (ret = create_comm(IMPI_CLIENT_SIZE, true)) ||
        OMPI_SUCCESS != (ret = create_comm(IMPI_CLIENT_COLOR, true)) ||
        OMPI_SUCCESS != (ret = create_comm(IMPI_HOST_SIZE, true)) ||
        OMPI_SUCCESS != (ret = create_comm(IMPI_HOST_COLOR, true)) ||
#endif
        0) {
        return ret;
    }
