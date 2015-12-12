switch (token) {
		case Opt_integrity:
			*flag &= ~JFS_NOINTEGRITY;
			break;
		case Opt_nointegrity:
			*flag |= JFS_NOINTEGRITY;
			break;
		case Opt_ignore:
			/* Silently ignore the quota options */
			/* Don't do anything ;-) */
			break;
		case Opt_iocharset:
			if (nls_map && nls_map != (void *) -1)
				unload_nls(nls_map);
			if (!strcmp(args[0].from, "none"))
				nls_map = NULL;
			else {
				nls_map = load_nls(args[0].from);
				if (!nls_map) {
					pr_err("JFS: charset not found\n");
					goto cleanup;
				}
			}
			break;
		case Opt_resize:
		{
			char *resize = args[0].from;
			*newLVSize = simple_strtoull(resize, &resize, 0);
			break;
		}
		case Opt_resize_nosize:
		{
			*newLVSize = sb->s_bdev->bd_inode->i_size >>
				sb->s_blocksize_bits;
			if (*newLVSize == 0)
				pr_err("JFS: Cannot determine volume size\n");
			break;
		}
		case Opt_errors:
		{
			char *errors = args[0].from;
			if (!errors || !*errors)
				goto cleanup;
			if (!strcmp(errors, "continue")) {
				*flag &= ~JFS_ERR_REMOUNT_RO;
				*flag &= ~JFS_ERR_PANIC;
				*flag |= JFS_ERR_CONTINUE;
			} else if (!strcmp(errors, "remount-ro")) {
				*flag &= ~JFS_ERR_CONTINUE;
				*flag &= ~JFS_ERR_PANIC;
				*flag |= JFS_ERR_REMOUNT_RO;
			} else if (!strcmp(errors, "panic")) {
				*flag &= ~JFS_ERR_CONTINUE;
				*flag &= ~JFS_ERR_REMOUNT_RO;
				*flag |= JFS_ERR_PANIC;
			} else {
				pr_err("JFS: %s is an invalid error handler\n",
				       errors);
				goto cleanup;
			}
			break;
		}

#ifdef CONFIG_QUOTA
		case Opt_quota:
		case Opt_usrquota:
			*flag |= JFS_USRQUOTA;
			break;
		case Opt_grpquota:
			*flag |= JFS_GRPQUOTA;
			break;
#else
		case Opt_usrquota:
		case Opt_grpquota:
		case Opt_quota:
			pr_err("JFS: quota operations not supported\n");
			break;
#endif
		case Opt_uid:
		{
			char *uid = args[0].from;
			uid_t val = simple_strtoul(uid, &uid, 0);
			sbi->uid = make_kuid(current_user_ns(), val);
			if (!uid_valid(sbi->uid))
				goto cleanup;
			break;
		}

		case Opt_gid:
		{
			char *gid = args[0].from;
			gid_t val = simple_strtoul(gid, &gid, 0);
			sbi->gid = make_kgid(current_user_ns(), val);
			if (!gid_valid(sbi->gid))
				goto cleanup;
			break;
		}

		case Opt_umask:
		{
			char *umask = args[0].from;
			sbi->umask = simple_strtoul(umask, &umask, 8);
			if (sbi->umask & ~0777) {
				pr_err("JFS: Invalid value of umask\n");
				goto cleanup;
			}
			break;
		}

		case Opt_discard:
		{
			struct request_queue *q = bdev_get_queue(sb->s_bdev);
			/* if set to 1, even copying files will cause
			 * trimming :O
			 * -> user has more control over the online trimming
			 */
			sbi->minblks_trim = 64;
			if (blk_queue_discard(q)) {
				*flag |= JFS_DISCARD;
			} else {
				pr_err("JFS: discard option " \
					"not supported on device\n");
			}
			break;
		}

		case Opt_nodiscard:
			*flag &= ~JFS_DISCARD;
			break;

		case Opt_discard_minblk:
		{
			struct request_queue *q = bdev_get_queue(sb->s_bdev);
			char *minblks_trim = args[0].from;
			if (blk_queue_discard(q)) {
				*flag |= JFS_DISCARD;
				sbi->minblks_trim = simple_strtoull(
					minblks_trim, &minblks_trim, 0);
			} else {
				pr_err("JFS: discard option " \
					"not supported on device\n");
			}
			break;
		}

		default:
			printk("jfs: Unrecognized mount option \"%s\" "
					" or missing value\n", p);
			goto cleanup;
		}
