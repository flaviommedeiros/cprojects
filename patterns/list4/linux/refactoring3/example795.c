switch (token) {
		case Opt_degraded:
			btrfs_info(root->fs_info, "allowing degraded mounts");
			btrfs_set_opt(info->mount_opt, DEGRADED);
			break;
		case Opt_subvol:
		case Opt_subvolid:
		case Opt_subvolrootid:
		case Opt_device:
			/*
			 * These are parsed by btrfs_parse_early_options
			 * and can be happily ignored here.
			 */
			break;
		case Opt_nodatasum:
			btrfs_set_and_info(root, NODATASUM,
					   "setting nodatasum");
			break;
		case Opt_datasum:
			if (btrfs_test_opt(root, NODATASUM)) {
				if (btrfs_test_opt(root, NODATACOW))
					btrfs_info(root->fs_info, "setting datasum, datacow enabled");
				else
					btrfs_info(root->fs_info, "setting datasum");
			}
			btrfs_clear_opt(info->mount_opt, NODATACOW);
			btrfs_clear_opt(info->mount_opt, NODATASUM);
			break;
		case Opt_nodatacow:
			if (!btrfs_test_opt(root, NODATACOW)) {
				if (!btrfs_test_opt(root, COMPRESS) ||
				    !btrfs_test_opt(root, FORCE_COMPRESS)) {
					btrfs_info(root->fs_info,
						   "setting nodatacow, compression disabled");
				} else {
					btrfs_info(root->fs_info, "setting nodatacow");
				}
			}
			btrfs_clear_opt(info->mount_opt, COMPRESS);
			btrfs_clear_opt(info->mount_opt, FORCE_COMPRESS);
			btrfs_set_opt(info->mount_opt, NODATACOW);
			btrfs_set_opt(info->mount_opt, NODATASUM);
			break;
		case Opt_datacow:
			btrfs_clear_and_info(root, NODATACOW,
					     "setting datacow");
			break;
		case Opt_compress_force:
		case Opt_compress_force_type:
			compress_force = true;
			/* Fallthrough */
		case Opt_compress:
		case Opt_compress_type:
			if (token == Opt_compress ||
			    token == Opt_compress_force ||
			    strcmp(args[0].from, "zlib") == 0) {
				compress_type = "zlib";
				info->compress_type = BTRFS_COMPRESS_ZLIB;
				btrfs_set_opt(info->mount_opt, COMPRESS);
				btrfs_clear_opt(info->mount_opt, NODATACOW);
				btrfs_clear_opt(info->mount_opt, NODATASUM);
			} else if (strcmp(args[0].from, "lzo") == 0) {
				compress_type = "lzo";
				info->compress_type = BTRFS_COMPRESS_LZO;
				btrfs_set_opt(info->mount_opt, COMPRESS);
				btrfs_clear_opt(info->mount_opt, NODATACOW);
				btrfs_clear_opt(info->mount_opt, NODATASUM);
				btrfs_set_fs_incompat(info, COMPRESS_LZO);
			} else if (strncmp(args[0].from, "no", 2) == 0) {
				compress_type = "no";
				btrfs_clear_opt(info->mount_opt, COMPRESS);
				btrfs_clear_opt(info->mount_opt, FORCE_COMPRESS);
				compress_force = false;
			} else {
				ret = -EINVAL;
				goto out;
			}

			if (compress_force) {
				btrfs_set_and_info(root, FORCE_COMPRESS,
						   "force %s compression",
						   compress_type);
			} else {
				if (!btrfs_test_opt(root, COMPRESS))
					btrfs_info(root->fs_info,
						   "btrfs: use %s compression",
						   compress_type);
				/*
				 * If we remount from compress-force=xxx to
				 * compress=xxx, we need clear FORCE_COMPRESS
				 * flag, otherwise, there is no way for users
				 * to disable forcible compression separately.
				 */
				btrfs_clear_opt(info->mount_opt, FORCE_COMPRESS);
			}
			break;
		case Opt_ssd:
			btrfs_set_and_info(root, SSD,
					   "use ssd allocation scheme");
			break;
		case Opt_ssd_spread:
			btrfs_set_and_info(root, SSD_SPREAD,
					   "use spread ssd allocation scheme");
			btrfs_set_opt(info->mount_opt, SSD);
			break;
		case Opt_nossd:
			btrfs_set_and_info(root, NOSSD,
					     "not using ssd allocation scheme");
			btrfs_clear_opt(info->mount_opt, SSD);
			break;
		case Opt_barrier:
			btrfs_clear_and_info(root, NOBARRIER,
					     "turning on barriers");
			break;
		case Opt_nobarrier:
			btrfs_set_and_info(root, NOBARRIER,
					   "turning off barriers");
			break;
		case Opt_thread_pool:
			ret = match_int(&args[0], &intarg);
			if (ret) {
				goto out;
			} else if (intarg > 0) {
				info->thread_pool_size = intarg;
			} else {
				ret = -EINVAL;
				goto out;
			}
			break;
		case Opt_max_inline:
			num = match_strdup(&args[0]);
			if (num) {
				info->max_inline = memparse(num, NULL);
				kfree(num);

				if (info->max_inline) {
					info->max_inline = min_t(u64,
						info->max_inline,
						root->sectorsize);
				}
				btrfs_info(root->fs_info, "max_inline at %llu",
					info->max_inline);
			} else {
				ret = -ENOMEM;
				goto out;
			}
			break;
		case Opt_alloc_start:
			num = match_strdup(&args[0]);
			if (num) {
				mutex_lock(&info->chunk_mutex);
				info->alloc_start = memparse(num, NULL);
				mutex_unlock(&info->chunk_mutex);
				kfree(num);
				btrfs_info(root->fs_info, "allocations start at %llu",
					info->alloc_start);
			} else {
				ret = -ENOMEM;
				goto out;
			}
			break;
		case Opt_acl:
#ifdef CONFIG_BTRFS_FS_POSIX_ACL
			root->fs_info->sb->s_flags |= MS_POSIXACL;
			break;
#else
			btrfs_err(root->fs_info,
				"support for ACL not compiled in!");
			ret = -EINVAL;
			goto out;
#endif
		case Opt_noacl:
			root->fs_info->sb->s_flags &= ~MS_POSIXACL;
			break;
		case Opt_notreelog:
			btrfs_set_and_info(root, NOTREELOG,
					   "disabling tree log");
			break;
		case Opt_treelog:
			btrfs_clear_and_info(root, NOTREELOG,
					     "enabling tree log");
			break;
		case Opt_flushoncommit:
			btrfs_set_and_info(root, FLUSHONCOMMIT,
					   "turning on flush-on-commit");
			break;
		case Opt_noflushoncommit:
			btrfs_clear_and_info(root, FLUSHONCOMMIT,
					     "turning off flush-on-commit");
			break;
		case Opt_ratio:
			ret = match_int(&args[0], &intarg);
			if (ret) {
				goto out;
			} else if (intarg >= 0) {
				info->metadata_ratio = intarg;
				btrfs_info(root->fs_info, "metadata ratio %d",
				       info->metadata_ratio);
			} else {
				ret = -EINVAL;
				goto out;
			}
			break;
		case Opt_discard:
			btrfs_set_and_info(root, DISCARD,
					   "turning on discard");
			break;
		case Opt_nodiscard:
			btrfs_clear_and_info(root, DISCARD,
					     "turning off discard");
			break;
		case Opt_space_cache:
			btrfs_set_and_info(root, SPACE_CACHE,
					   "enabling disk space caching");
			break;
		case Opt_rescan_uuid_tree:
			btrfs_set_opt(info->mount_opt, RESCAN_UUID_TREE);
			break;
		case Opt_no_space_cache:
			btrfs_clear_and_info(root, SPACE_CACHE,
					     "disabling disk space caching");
			break;
		case Opt_inode_cache:
			btrfs_set_pending_and_info(info, INODE_MAP_CACHE,
					   "enabling inode map caching");
			break;
		case Opt_noinode_cache:
			btrfs_clear_pending_and_info(info, INODE_MAP_CACHE,
					     "disabling inode map caching");
			break;
		case Opt_clear_cache:
			btrfs_set_and_info(root, CLEAR_CACHE,
					   "force clearing of disk cache");
			break;
		case Opt_user_subvol_rm_allowed:
			btrfs_set_opt(info->mount_opt, USER_SUBVOL_RM_ALLOWED);
			break;
		case Opt_enospc_debug:
			btrfs_set_opt(info->mount_opt, ENOSPC_DEBUG);
			break;
		case Opt_noenospc_debug:
			btrfs_clear_opt(info->mount_opt, ENOSPC_DEBUG);
			break;
		case Opt_defrag:
			btrfs_set_and_info(root, AUTO_DEFRAG,
					   "enabling auto defrag");
			break;
		case Opt_nodefrag:
			btrfs_clear_and_info(root, AUTO_DEFRAG,
					     "disabling auto defrag");
			break;
		case Opt_recovery:
			btrfs_info(root->fs_info, "enabling auto recovery");
			btrfs_set_opt(info->mount_opt, RECOVERY);
			break;
		case Opt_skip_balance:
			btrfs_set_opt(info->mount_opt, SKIP_BALANCE);
			break;
#ifdef CONFIG_BTRFS_FS_CHECK_INTEGRITY
		case Opt_check_integrity_including_extent_data:
			btrfs_info(root->fs_info,
				   "enabling check integrity including extent data");
			btrfs_set_opt(info->mount_opt,
				      CHECK_INTEGRITY_INCLUDING_EXTENT_DATA);
			btrfs_set_opt(info->mount_opt, CHECK_INTEGRITY);
			break;
		case Opt_check_integrity:
			btrfs_info(root->fs_info, "enabling check integrity");
			btrfs_set_opt(info->mount_opt, CHECK_INTEGRITY);
			break;
		case Opt_check_integrity_print_mask:
			ret = match_int(&args[0], &intarg);
			if (ret) {
				goto out;
			} else if (intarg >= 0) {
				info->check_integrity_print_mask = intarg;
				btrfs_info(root->fs_info, "check_integrity_print_mask 0x%x",
				       info->check_integrity_print_mask);
			} else {
				ret = -EINVAL;
				goto out;
			}
			break;
#else
		case Opt_check_integrity_including_extent_data:
		case Opt_check_integrity:
		case Opt_check_integrity_print_mask:
			btrfs_err(root->fs_info,
				"support for check_integrity* not compiled in!");
			ret = -EINVAL;
			goto out;
#endif
		case Opt_fatal_errors:
			if (strcmp(args[0].from, "panic") == 0)
				btrfs_set_opt(info->mount_opt,
					      PANIC_ON_FATAL_ERROR);
			else if (strcmp(args[0].from, "bug") == 0)
				btrfs_clear_opt(info->mount_opt,
					      PANIC_ON_FATAL_ERROR);
			else {
				ret = -EINVAL;
				goto out;
			}
			break;
		case Opt_commit_interval:
			intarg = 0;
			ret = match_int(&args[0], &intarg);
			if (ret < 0) {
				btrfs_err(root->fs_info, "invalid commit interval");
				ret = -EINVAL;
				goto out;
			}
			if (intarg > 0) {
				if (intarg > 300) {
					btrfs_warn(root->fs_info, "excessive commit interval %d",
							intarg);
				}
				info->commit_interval = intarg;
			} else {
				btrfs_info(root->fs_info, "using default commit interval %ds",
				    BTRFS_DEFAULT_COMMIT_INTERVAL);
				info->commit_interval = BTRFS_DEFAULT_COMMIT_INTERVAL;
			}
			break;
#ifdef CONFIG_BTRFS_DEBUG
		case Opt_fragment_all:
			btrfs_info(root->fs_info, "fragmenting all space");
			btrfs_set_opt(info->mount_opt, FRAGMENT_DATA);
			btrfs_set_opt(info->mount_opt, FRAGMENT_METADATA);
			break;
		case Opt_fragment_metadata:
			btrfs_info(root->fs_info, "fragmenting metadata");
			btrfs_set_opt(info->mount_opt,
				      FRAGMENT_METADATA);
			break;
		case Opt_fragment_data:
			btrfs_info(root->fs_info, "fragmenting data");
			btrfs_set_opt(info->mount_opt, FRAGMENT_DATA);
			break;
#endif
		case Opt_err:
			btrfs_info(root->fs_info, "unrecognized mount option '%s'", p);
			ret = -EINVAL;
			goto out;
		default:
			break;
		}
