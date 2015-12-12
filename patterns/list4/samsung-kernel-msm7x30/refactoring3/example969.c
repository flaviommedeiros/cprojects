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
					printk(KERN_ERR
					       "JFS: charset not found\n");
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
				printk(KERN_ERR
				       "JFS: Cannot determine volume size\n");
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
				printk(KERN_ERR
				       "JFS: %s is an invalid error handler\n",
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
			printk(KERN_ERR
			       "JFS: quota operations not supported\n");
			break;
#endif
		case Opt_uid:
		{
			char *uid = args[0].from;
			sbi->uid = simple_strtoul(uid, &uid, 0);
			break;
		}
		case Opt_gid:
		{
			char *gid = args[0].from;
			sbi->gid = simple_strtoul(gid, &gid, 0);
			break;
		}
		case Opt_umask:
		{
			char *umask = args[0].from;
			sbi->umask = simple_strtoul(umask, &umask, 8);
			if (sbi->umask & ~0777) {
				printk(KERN_ERR
				       "JFS: Invalid value of umask\n");
				goto cleanup;
			}
			break;
		}
		default:
			printk("jfs: Unrecognized mount option \"%s\" "
					" or missing value\n", p);
			goto cleanup;
		}
