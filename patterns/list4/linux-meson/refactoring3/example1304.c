switch (token) {
		case Opt_gc_background_off:
			clear_opt(sbi, BG_GC);
			break;
		case Opt_disable_roll_forward:
			set_opt(sbi, DISABLE_ROLL_FORWARD);
			break;
		case Opt_discard:
			set_opt(sbi, DISCARD);
			break;
		case Opt_noheap:
			set_opt(sbi, NOHEAP);
			break;
#ifdef CONFIG_F2FS_FS_XATTR
		case Opt_nouser_xattr:
			clear_opt(sbi, XATTR_USER);
			break;
#else
		case Opt_nouser_xattr:
			f2fs_msg(sb, KERN_INFO,
				"nouser_xattr options not supported");
			break;
#endif
#ifdef CONFIG_F2FS_FS_POSIX_ACL
		case Opt_noacl:
			clear_opt(sbi, POSIX_ACL);
			break;
#else
		case Opt_noacl:
			f2fs_msg(sb, KERN_INFO, "noacl options not supported");
			break;
#endif
		case Opt_active_logs:
			if (args->from && match_int(args, &arg))
				return -EINVAL;
			if (arg != 2 && arg != 4 && arg != NR_CURSEG_TYPE)
				return -EINVAL;
			sbi->active_logs = arg;
			break;
		case Opt_disable_ext_identify:
			set_opt(sbi, DISABLE_EXT_IDENTIFY);
			break;
		default:
			f2fs_msg(sb, KERN_ERR,
				"Unrecognized mount option \"%s\" or missing value",
				p);
			return -EINVAL;
		}
