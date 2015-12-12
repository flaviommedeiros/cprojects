switch (token) {
		case Opt_hb_local:
			mopt->mount_opt |= OCFS2_MOUNT_HB_LOCAL;
			break;
		case Opt_hb_none:
			mopt->mount_opt &= ~OCFS2_MOUNT_HB_LOCAL;
			break;
		case Opt_barrier:
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option)
				mopt->mount_opt |= OCFS2_MOUNT_BARRIER;
			else
				mopt->mount_opt &= ~OCFS2_MOUNT_BARRIER;
			break;
		case Opt_intr:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOINTR;
			break;
		case Opt_nointr:
			mopt->mount_opt |= OCFS2_MOUNT_NOINTR;
			break;
		case Opt_err_panic:
			mopt->mount_opt |= OCFS2_MOUNT_ERRORS_PANIC;
			break;
		case Opt_err_ro:
			mopt->mount_opt &= ~OCFS2_MOUNT_ERRORS_PANIC;
			break;
		case Opt_data_ordered:
			mopt->mount_opt &= ~OCFS2_MOUNT_DATA_WRITEBACK;
			break;
		case Opt_data_writeback:
			mopt->mount_opt |= OCFS2_MOUNT_DATA_WRITEBACK;
			break;
		case Opt_user_xattr:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOUSERXATTR;
			break;
		case Opt_nouser_xattr:
			mopt->mount_opt |= OCFS2_MOUNT_NOUSERXATTR;
			break;
		case Opt_atime_quantum:
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option >= 0)
				mopt->atime_quantum = option;
			break;
		case Opt_slot:
			option = 0;
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option)
				mopt->slot = (s16)option;
			break;
		case Opt_commit:
			option = 0;
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option < 0)
				return 0;
			if (option == 0)
				option = JBD2_DEFAULT_MAX_COMMIT_AGE;
			mopt->commit_interval = HZ * option;
			break;
		case Opt_localalloc:
			option = 0;
			if (match_int(&args[0], &option)) {
				status = 0;
				goto bail;
			}
			if (option >= 0 && (option <= ocfs2_local_alloc_size(sb) * 8))
				mopt->localalloc_opt = option;
			break;
		case Opt_localflocks:
			/*
			 * Changing this during remount could race
			 * flock() requests, or "unbalance" existing
			 * ones (e.g., a lock is taken in one mode but
			 * dropped in the other). If users care enough
			 * to flip locking modes during remount, we
			 * could add a "local" flag to individual
			 * flock structures for proper tracking of
			 * state.
			 */
			if (!is_remount)
				mopt->mount_opt |= OCFS2_MOUNT_LOCALFLOCKS;
			break;
		case Opt_stack:
			/* Check both that the option we were passed
			 * is of the right length and that it is a proper
			 * string of the right length.
			 */
			if (((args[0].to - args[0].from) !=
			     OCFS2_STACK_LABEL_LEN) ||
			    (strnlen(args[0].from,
				     OCFS2_STACK_LABEL_LEN) !=
			     OCFS2_STACK_LABEL_LEN)) {
				mlog(ML_ERROR,
				     "Invalid cluster_stack option\n");
				status = 0;
				goto bail;
			}
			memcpy(mopt->cluster_stack, args[0].from,
			       OCFS2_STACK_LABEL_LEN);
			mopt->cluster_stack[OCFS2_STACK_LABEL_LEN] = '\0';
			break;
		case Opt_inode64:
			mopt->mount_opt |= OCFS2_MOUNT_INODE64;
			break;
		case Opt_usrquota:
			/* We check only on remount, otherwise features
			 * aren't yet initialized. */
			if (is_remount && !OCFS2_HAS_RO_COMPAT_FEATURE(sb,
			    OCFS2_FEATURE_RO_COMPAT_USRQUOTA)) {
				mlog(ML_ERROR, "User quota requested but "
				     "filesystem feature is not set\n");
				status = 0;
				goto bail;
			}
			mopt->mount_opt |= OCFS2_MOUNT_USRQUOTA;
			break;
		case Opt_grpquota:
			if (is_remount && !OCFS2_HAS_RO_COMPAT_FEATURE(sb,
			    OCFS2_FEATURE_RO_COMPAT_GRPQUOTA)) {
				mlog(ML_ERROR, "Group quota requested but "
				     "filesystem feature is not set\n");
				status = 0;
				goto bail;
			}
			mopt->mount_opt |= OCFS2_MOUNT_GRPQUOTA;
			break;
#ifdef CONFIG_OCFS2_FS_POSIX_ACL
		case Opt_acl:
			mopt->mount_opt |= OCFS2_MOUNT_POSIX_ACL;
			break;
		case Opt_noacl:
			mopt->mount_opt &= ~OCFS2_MOUNT_POSIX_ACL;
			break;
#else
		case Opt_acl:
		case Opt_noacl:
			printk(KERN_INFO "ocfs2 (no)acl options not supported\n");
			break;
#endif
		default:
			mlog(ML_ERROR,
			     "Unrecognized mount option \"%s\" "
			     "or missing value\n", p);
			status = 0;
			goto bail;
		}
