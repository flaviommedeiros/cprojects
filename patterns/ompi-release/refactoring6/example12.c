if (OMPI_SUCCESS != (ret = free_comm(MPI_TAG_UB)) ||
        OMPI_SUCCESS != (ret = free_comm(MPI_HOST)) ||
        OMPI_SUCCESS != (ret = free_comm(MPI_IO)) ||
        OMPI_SUCCESS != (ret = free_comm(MPI_WTIME_IS_GLOBAL)) ||
        OMPI_SUCCESS != (ret = free_comm(MPI_APPNUM)) ||
        OMPI_SUCCESS != (ret = free_comm(MPI_LASTUSEDCODE)) ||
        OMPI_SUCCESS != (ret = free_comm(MPI_UNIVERSE_SIZE)) ||
        OMPI_SUCCESS != (ret = free_win(MPI_WIN_BASE)) ||
        OMPI_SUCCESS != (ret = free_win(MPI_WIN_SIZE)) ||
        OMPI_SUCCESS != (ret = free_win(MPI_WIN_DISP_UNIT)) ||
        OMPI_SUCCESS != (ret = free_win(MPI_WIN_CREATE_FLAVOR)) ||
        OMPI_SUCCESS != (ret = free_win(MPI_WIN_MODEL)) ||
#if 0
        /* JMS For when we implement IMPI */
        OMPI_SUCCESS != (ret = free_comm(IMPI_CLIENT_SIZE)) ||
        OMPI_SUCCESS != (ret = free_comm(IMPI_CLIENT_COLOR)) ||
        OMPI_SUCCESS != (ret = free_comm(IMPI_HOST_SIZE)) ||
        OMPI_SUCCESS != (ret = free_comm(IMPI_HOST_COLOR)) ||
#endif
        0) {
        return ret;
    }
