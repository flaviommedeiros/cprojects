#ifdef HAVE_MPI
if (mpi_p > 1) {
			int i;

			for (i = 0; i < mpi_p; i++) {
				if (i == mpi_id)
					continue;
				if (mpi_req[i] == NULL)
					mpi_req[i] = mem_alloc_tiny(
						sizeof(MPI_Request),
						MEM_ALIGN_WORD);
				else
					if (*mpi_req[i] != MPI_REQUEST_NULL)
						continue;
				MPI_Isend("r", 1, MPI_CHAR, i, JOHN_MPI_RELOAD,
				          MPI_COMM_WORLD, mpi_req[i]);
			}
		} else
#endif
		if (options.fork)
			raise(SIGUSR2);
