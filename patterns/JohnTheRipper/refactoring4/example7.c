#ifndef HAVE_MPI
if (options.fork)
#else
		if (options.fork || mpi_p > 1)
#endif
			fprintf(stderr, "%u ", options.node_min);
