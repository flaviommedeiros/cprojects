switch (ch) {
		case 'd':
			debug++;
			break;
		case 'c':
			chroot_path = optarg;
			break;
		case 'C':
			conffile = optarg;
			break;
		case 'R':
			reposdir = optarg;
			break;
		case 'r':
			rootdir = optarg;
			break;
#ifdef HAVE_LIBJAIL
		case 'j':
			jail_str = optarg;
			break;
#endif
		case 'l':
			show_commands = true;
			break;
		case 'N':
			activation_test = true;
			break;
		case 'v':
			version++;
			break;
		case 'o':
			export_arg_option (optarg);
			break;
		case '4':
			init_flags = PKG_INIT_FLAG_USE_IPV4;
			break;
		case '6':
			init_flags = PKG_INIT_FLAG_USE_IPV6;
			break;
		default:
			break;
		}
