switch (token) {
		case Opt_gc_background:
			name = match_strdup(&args[0]);

			if (!name)
				return -ENOMEM;
			if (strlen(name) == 2 && !strncmp(name, "on", 2))
				set_opt(sbi, BG_GC);
			else if (strlen(name) == 3 && !strncmp(name, "off", 3))
				clear_opt(sbi, BG_GC);
			else {
				kfree(name);
				return -EINVAL;
			}
			kfree(name);
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
		case Opt_user_xattr:
			set_opt(sbi, XATTR_USER);
			break;
		case Opt_nouser_xattr:
			clear_opt(sbi, XATTR_USER);
			break;
		case Opt_inline_xattr:
			set_opt(sbi, INLINE_XATTR);
			break;
#else
		case Opt_user_xattr:
			f2fs_msg(sb, KERN_INFO,
				"user_xattr options not supported");
			break;
		case Opt_nouser_xattr:
			f2fs_msg(sb, KERN_INFO,
				"nouser_xattr options not supported");
			break;
		case Opt_inline_xattr:
			f2fs_msg(sb, KERN_INFO,
				"inline_xattr options not supported");
			break;
#endif
#ifdef CONFIG_F2FS_FS_POSIX_ACL
		case Opt_acl:
			set_opt(sbi, POSIX_ACL);
			break;
		case Opt_noacl:
			clear_opt(sbi, POSIX_ACL);
			break;
#else
		case Opt_acl:
			f2fs_msg(sb, KERN_INFO, "acl options not supported");
			break;
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
		case Opt_inline_data:
			set_opt(sbi, INLINE_DATA);
			break;
		case Opt_inline_dentry:
			set_opt(sbi, INLINE_DENTRY);
			break;
		case Opt_flush_merge:
			set_opt(sbi, FLUSH_MERGE);
			break;
		case Opt_nobarrier:
			set_opt(sbi, NOBARRIER);
			break;
		case Opt_fastboot:
			set_opt(sbi, FASTBOOT);
			break;
		default:
			f2fs_msg(sb, KERN_ERR,
				"Unrecognized mount option \"%s\" or missing value",
				p);
			return -EINVAL;
		}
