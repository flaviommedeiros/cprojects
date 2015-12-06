#ifdef HAVE_MPI
if (!strncmp(*opt, "--fork", 6))
			fake_fork = 0;
		else
#endif
		if (!strncmp(*opt, "--encoding", 10) ||
			!strncmp(*opt, "--input-encoding", 16))
			add_enc = 0;
		else if (!strncmp(*opt, "--internal-codepage", 19) ||
		         !strncmp(*opt, "--internal-encoding", 19) ||
		         !strncmp(*opt, "--target-encoding", 17))
			add_2nd_enc = 0;
		else if (!strncmp(*opt, "--mkv-stats", 11))
			add_mkv_stats = 0;
