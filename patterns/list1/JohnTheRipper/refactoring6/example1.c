if (!options.fork &&
#ifdef HAVE_MPI
		         mpi_p == 1 &&
#endif
		    options.node_max - options.node_min + 1 ==
		    options.node_count)
			msg = "node numbers can't span the whole range";
