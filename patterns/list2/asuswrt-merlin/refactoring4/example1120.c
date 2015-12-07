#ifdef KERNEL_64_USERSPACE_32
if (string_to_number_ll(optarg, 0, 0, 
				     &markinfo->mark))
#else
		if (string_to_number_l(optarg, 0, 0, 
				     &markinfo->mark))
#endif
			exit_error(PARAMETER_PROBLEM, "Bad MARK value `%s'", optarg);
