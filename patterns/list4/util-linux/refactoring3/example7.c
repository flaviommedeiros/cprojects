switch (c) {
		case 'h':
			usage(EXIT_SUCCESS);
		case 'V':
			printf(UTIL_LINUX_VERSION);
			return EXIT_SUCCESS;
		case 't':
			namespace_target_pid =
			    strtoul_or_err(optarg, _("failed to parse pid"));
			break;
		case 'm':
			if (optarg)
				open_namespace_fd(CLONE_NEWNS, optarg);
			else
				namespaces |= CLONE_NEWNS;
			break;
		case 'u':
			if (optarg)
				open_namespace_fd(CLONE_NEWUTS, optarg);
			else
				namespaces |= CLONE_NEWUTS;
			break;
		case 'i':
			if (optarg)
				open_namespace_fd(CLONE_NEWIPC, optarg);
			else
				namespaces |= CLONE_NEWIPC;
			break;
		case 'n':
			if (optarg)
				open_namespace_fd(CLONE_NEWNET, optarg);
			else
				namespaces |= CLONE_NEWNET;
			break;
		case 'p':
			if (optarg)
				open_namespace_fd(CLONE_NEWPID, optarg);
			else
				namespaces |= CLONE_NEWPID;
			break;
		case 'U':
			if (optarg)
				open_namespace_fd(CLONE_NEWUSER, optarg);
			else
				namespaces |= CLONE_NEWUSER;
			break;
		case 'S':
			uid = strtoul_or_err(optarg, _("failed to parse uid"));
			force_uid = true;
			break;
		case 'G':
			gid = strtoul_or_err(optarg, _("failed to parse gid"));
			force_gid = true;
			break;
		case 'F':
			do_fork = 0;
			break;
		case 'r':
			if (optarg)
				open_target_fd(&root_fd, "root", optarg);
			else
				do_rd = true;
			break;
		case 'w':
			if (optarg)
				open_target_fd(&wd_fd, "cwd", optarg);
			else
				do_wd = true;
			break;
		case OPT_PRESERVE_CRED:
			preserve_cred = 1;
			break;
#ifdef HAVE_LIBSELINUX
		case 'Z':
			selinux = 1;
			break;
#endif
		default:
			usage(EXIT_FAILURE);
		}
