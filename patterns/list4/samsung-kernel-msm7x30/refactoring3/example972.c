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
			set_opt (sbi->s_mount_opt, OLDALLOC);
			break;
		case Opt_orlov:
			clear_opt (sbi->s_mount_opt, OLDALLOC);
			break;
		case Opt_nobh:
			set_opt (sbi->s_mount_opt, NOBH);
			break;
#ifdef CONFIG_EXT2_FS_XATTR
		case Opt_user_xattr:
			set_opt (sbi->s_mount_opt, XATTR_USER);
			break;
		case Opt_nouser_xattr:
			clear_opt (sbi->s_mount_opt, XATTR_USER);
			break;
#else
		case Opt_user_xattr:
		case Opt_nouser_xattr:
			ext2_msg(sb, KERN_INFO, "(no)user_xattr options"
				"not supported");
			break;
#endif
#ifdef CONFIG_EXT2_FS_POSIX_ACL
		case Opt_acl:
			set_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
		case Opt_noacl:
			clear_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
#else
		case Opt_acl:
		case Opt_noacl:
			ext2_msg(sb, KERN_INFO,
				"(no)acl options not supported");
			break;
#endif
		case Opt_xip:
#ifdef CONFIG_EXT2_FS_XIP
			set_opt (sbi->s_mount_opt, XIP);
#else
			ext2_msg(sb, KERN_INFO, "xip option not supported");
#endif
			break;

#if defined(CONFIG_QUOTA)
		case Opt_quota:
		case Opt_usrquota:
			set_opt(sbi->s_mount_opt, USRQUOTA);
			break;

		case Opt_grpquota:
			set_opt(sbi->s_mount_opt, GRPQUOTA);
			break;
#else
		case Opt_quota:
		case Opt_usrquota:
		case Opt_grpquota:
			ext2_msg(sb, KERN_INFO,
				"quota operations not supported");
			break;
#endif

		case Opt_reservation:
			set_opt(sbi->s_mount_opt, RESERVATION);
			ext2_msg(sb, KERN_INFO, "reservations ON");
			break;
		case Opt_noreservation:
			clear_opt(sbi->s_mount_opt, RESERVATION);
			ext2_msg(sb, KERN_INFO, "reservations OFF");
			break;
		case Opt_ignore:
			break;
		default:
			return 0;
		}
