#if HAVE_MPI
if (mpi_p == 1)
#endif
	if (database.format && database.format->params.label &&
	        (!strstr(database.format->params.label, "-opencl") &&
	         !strstr(database.format->params.label, "-cuda")))
	if (!options.fork && john_omp_threads_orig > 1 &&
	    database.format && database.format != &dummy_format &&
	    !rec_restoring_now) {
		const char *msg = NULL;
		if (!(database.format->params.flags & FMT_OMP))
			msg = "no OpenMP support";
		else if ((database.format->params.flags & FMT_OMP_BAD))
			msg = "poor OpenMP scalability";
		if (msg)
#if OS_FORK
			fprintf(stderr, "Warning: %s for this hash type, "
			    "consider --fork=%d\n",
			    msg, john_omp_threads_orig);
#else
			fprintf(stderr, "Warning: %s for this hash type\n",
			    msg);
#endif
	}
