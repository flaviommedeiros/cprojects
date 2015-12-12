switch (token) {
		case Opt_bsd_df:
			clear_opt (sbi->s_mount_opt, MINIX_DF);
			break;
		case Opt_minix_df:
			set_opt (sbi->s_mount_opt, MINIX_DF);
			break;
		case Opt_grpid:
			set_opt (sbi->s_mount_opt, GRPID);
			break;
		case Opt_nogrpid:
			clear_opt (sbi->s_mount_opt, GRPID);
			break;
		case Opt_resuid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_resuid = option;
			break;
		case Opt_resgid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_resgid = option;
			break;
		case Opt_sb:
			/* handled by get_sb_block() instead of here */
			/* *sb_block = match_int(&args[0]); */
			break;
		case Opt_err_panic:
			clear_opt (sbi->s_mount_opt, ERRORS_CONT);
			clear_opt (sbi->s_mount_opt, ERRORS_RO);
			set_opt (sbi->s_mount_opt, ERRORS_PANIC);
			break;
		case Opt_err_ro:
			clear_opt (sbi->s_mount_opt, ERRORS_CONT);
			clear_opt (sbi->s_mount_opt, ERRORS_PANIC);
			set_opt (sbi->s_mount_opt, ERRORS_RO);
			break;
		case Opt_err_cont:
			clear_opt (sbi->s_mount_opt, ERRORS_RO);
			clear_opt (sbi->s_mount_opt, ERRORS_PANIC);
			set_opt (sbi->s_mount_opt, ERRORS_CONT);
			break;
		case Opt_nouid32:
			set_opt (sbi->s_mount_opt, NO_UID32);
			break;
		case Opt_nocheck:
			clear_opt (sbi->s_mount_opt, CHECK);
			break;
		case Opt_debug:
			set_opt (sbi->s_mount_opt, DEBUG);
			break;
		case Opt_oldalloc:
			ext3_msg(sb, KERN_WARNING,
				"Ignoring deprecated oldalloc option");
			break;
		case Opt_orlov:
			ext3_msg(sb, KERN_WARNING,
				"Ignoring deprecated orlov option");
			break;
#ifdef CONFIG_EXT3_FS_XATTR
		case Opt_user_xattr:
			set_opt (sbi->s_mount_opt, XATTR_USER);
			break;
		case Opt_nouser_xattr:
			clear_opt (sbi->s_mount_opt, XATTR_USER);
			break;
#else
		case Opt_user_xattr:
		case Opt_nouser_xattr:
			ext3_msg(sb, KERN_INFO,
				"(no)user_xattr options not supported");
			break;
#endif
#ifdef CONFIG_EXT3_FS_POSIX_ACL
		case Opt_acl:
			set_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
		case Opt_noacl:
			clear_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
#else
		case Opt_acl:
		case Opt_noacl:
			ext3_msg(sb, KERN_INFO,
				"(no)acl options not supported");
			break;
#endif
		case Opt_reservation:
			set_opt(sbi->s_mount_opt, RESERVATION);
			break;
		case Opt_noreservation:
			clear_opt(sbi->s_mount_opt, RESERVATION);
			break;
		case Opt_journal_update:
			/* @@@ FIXME */
			/* Eventually we will want to be able to create
			   a journal file here.  For now, only allow the
			   user to specify an existing inode to be the
			   journal file. */
			if (is_remount) {
				ext3_msg(sb, KERN_ERR, "error: cannot specify "
					"journal on remount");
				return 0;
			}
			set_opt (sbi->s_mount_opt, UPDATE_JOURNAL);
			break;
		case Opt_journal_inum:
			if (is_remount) {
				ext3_msg(sb, KERN_ERR, "error: cannot specify "
				       "journal on remount");
				return 0;
			}
			if (match_int(&args[0], &option))
				return 0;
			*inum = option;
			break;
		case Opt_journal_dev:
			if (is_remount) {
				ext3_msg(sb, KERN_ERR, "error: cannot specify "
				       "journal on remount");
				return 0;
			}
			if (match_int(&args[0], &option))
				return 0;
			*journal_devnum = option;
			break;
		case Opt_noload:
			set_opt (sbi->s_mount_opt, NOLOAD);
			break;
		case Opt_commit:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0)
				return 0;
			if (option == 0)
				option = JBD_DEFAULT_MAX_COMMIT_AGE;
			sbi->s_commit_interval = HZ * option;
			break;
		case Opt_data_journal:
			data_opt = EXT3_MOUNT_JOURNAL_DATA;
			goto datacheck;
		case Opt_data_ordered:
			data_opt = EXT3_MOUNT_ORDERED_DATA;
			goto datacheck;
		case Opt_data_writeback:
			data_opt = EXT3_MOUNT_WRITEBACK_DATA;
		datacheck:
			if (is_remount) {
				if (test_opt(sb, DATA_FLAGS) == data_opt)
					break;
				ext3_msg(sb, KERN_ERR,
					"error: cannot change "
					"data mode on remount. The filesystem "
					"is mounted in data=%s mode and you "
					"try to remount it in data=%s mode.",
					data_mode_string(test_opt(sb,
							DATA_FLAGS)),
					data_mode_string(data_opt));
				return 0;
			} else {
				clear_opt(sbi->s_mount_opt, DATA_FLAGS);
				sbi->s_mount_opt |= data_opt;
			}
			break;
		case Opt_data_err_abort:
			set_opt(sbi->s_mount_opt, DATA_ERR_ABORT);
			break;
		case Opt_data_err_ignore:
			clear_opt(sbi->s_mount_opt, DATA_ERR_ABORT);
			break;
#ifdef CONFIG_QUOTA
		case Opt_usrjquota:
			if (!set_qf_name(sb, USRQUOTA, &args[0]))
				return 0;
			break;
		case Opt_grpjquota:
			if (!set_qf_name(sb, GRPQUOTA, &args[0]))
				return 0;
			break;
		case Opt_offusrjquota:
			if (!clear_qf_name(sb, USRQUOTA))
				return 0;
			break;
		case Opt_offgrpjquota:
			if (!clear_qf_name(sb, GRPQUOTA))
				return 0;
			break;
		case Opt_jqfmt_vfsold:
			qfmt = QFMT_VFS_OLD;
			goto set_qf_format;
		case Opt_jqfmt_vfsv0:
			qfmt = QFMT_VFS_V0;
			goto set_qf_format;
		case Opt_jqfmt_vfsv1:
			qfmt = QFMT_VFS_V1;
set_qf_format:
			if (sb_any_quota_loaded(sb) &&
			    sbi->s_jquota_fmt != qfmt) {
				ext3_msg(sb, KERN_ERR, "error: cannot change "
					"journaled quota options when "
					"quota turned on.");
				return 0;
			}
			sbi->s_jquota_fmt = qfmt;
			break;
		case Opt_quota:
		case Opt_usrquota:
			set_opt(sbi->s_mount_opt, QUOTA);
			set_opt(sbi->s_mount_opt, USRQUOTA);
			break;
		case Opt_grpquota:
			set_opt(sbi->s_mount_opt, QUOTA);
			set_opt(sbi->s_mount_opt, GRPQUOTA);
			break;
		case Opt_noquota:
			if (sb_any_quota_loaded(sb)) {
				ext3_msg(sb, KERN_ERR, "error: cannot change "
					"quota options when quota turned on.");
				return 0;
			}
			clear_opt(sbi->s_mount_opt, QUOTA);
			clear_opt(sbi->s_mount_opt, USRQUOTA);
			clear_opt(sbi->s_mount_opt, GRPQUOTA);
			break;
#else
		case Opt_quota:
		case Opt_usrquota:
		case Opt_grpquota:
			ext3_msg(sb, KERN_ERR,
				"error: quota options not supported.");
			break;
		case Opt_usrjquota:
		case Opt_grpjquota:
		case Opt_offusrjquota:
		case Opt_offgrpjquota:
		case Opt_jqfmt_vfsold:
		case Opt_jqfmt_vfsv0:
		case Opt_jqfmt_vfsv1:
			ext3_msg(sb, KERN_ERR,
				"error: journaled quota options not "
				"supported.");
			break;
		case Opt_noquota:
			break;
#endif
		case Opt_abort:
			set_opt(sbi->s_mount_opt, ABORT);
			break;
		case Opt_nobarrier:
			clear_opt(sbi->s_mount_opt, BARRIER);
			break;
		case Opt_barrier:
			if (args[0].from) {
				if (match_int(&args[0], &option))
					return 0;
			} else
				option = 1;	/* No argument, default to 1 */
			if (option)
				set_opt(sbi->s_mount_opt, BARRIER);
			else
				clear_opt(sbi->s_mount_opt, BARRIER);
			break;
		case Opt_ignore:
			break;
		case Opt_resize:
			if (!is_remount) {
				ext3_msg(sb, KERN_ERR,
					"error: resize option only available "
					"for remount");
				return 0;
			}
			if (match_int(&args[0], &option) != 0)
				return 0;
			*n_blocks_count = option;
			break;
		case Opt_nobh:
			ext3_msg(sb, KERN_WARNING,
				"warning: ignoring deprecated nobh option");
			break;
		case Opt_bh:
			ext3_msg(sb, KERN_WARNING,
				"warning: ignoring deprecated bh option");
			break;
		default:
			ext3_msg(sb, KERN_ERR,
				"error: unrecognized mount option \"%s\" "
				"or missing value", p);
			return 0;
		}
