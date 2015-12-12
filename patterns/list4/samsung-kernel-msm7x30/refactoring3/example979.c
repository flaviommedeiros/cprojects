switch (token) {
		case Opt_uid:
			if (match_int(&args[0], &option))
				return -EINVAL;
			opts->uid = option;
			opts->setuid = 1;
			break;
		case Opt_gid:
			if (match_int(&args[0], &option))
				return -EINVAL;
			opts->gid = option;
			opts->setgid = 1;
			break;
		case Opt_mode:
			if (match_octal(&args[0], &option))
				return -EINVAL;
			opts->mode = option & S_IALLUGO;
			break;
#ifdef CONFIG_DEVPTS_MULTIPLE_INSTANCES
		case Opt_ptmxmode:
			if (match_octal(&args[0], &option))
				return -EINVAL;
			opts->ptmxmode = option & S_IALLUGO;
			break;
		case Opt_newinstance:
			/* newinstance makes sense only on initial mount */
			if (op == PARSE_MOUNT)
				opts->newinstance = 1;
			break;
		case Opt_max:
			if (match_int(&args[0], &option) ||
			    option < 0 || option > NR_UNIX98_PTY_MAX)
				return -EINVAL;
			opts->max = option;
			break;
#endif
		default:
			printk(KERN_ERR "devpts: called with bogus options\n");
			return -EINVAL;
		}
