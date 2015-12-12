switch (token) {
		case Opt_novrs:
			uopt->novrs = 1;
			break;
		case Opt_bs:
			if (match_int(&args[0], &option))
				return 0;
			uopt->blocksize = option;
			uopt->flags |= (1 << UDF_FLAG_BLOCKSIZE_SET);
			break;
		case Opt_unhide:
			uopt->flags |= (1 << UDF_FLAG_UNHIDE);
			break;
		case Opt_undelete:
			uopt->flags |= (1 << UDF_FLAG_UNDELETE);
			break;
		case Opt_noadinicb:
			uopt->flags &= ~(1 << UDF_FLAG_USE_AD_IN_ICB);
			break;
		case Opt_adinicb:
			uopt->flags |= (1 << UDF_FLAG_USE_AD_IN_ICB);
			break;
		case Opt_shortad:
			uopt->flags |= (1 << UDF_FLAG_USE_SHORT_AD);
			break;
		case Opt_longad:
			uopt->flags &= ~(1 << UDF_FLAG_USE_SHORT_AD);
			break;
		case Opt_gid:
			if (match_int(args, &option))
				return 0;
			uopt->gid = make_kgid(current_user_ns(), option);
			if (!gid_valid(uopt->gid))
				return 0;
			uopt->flags |= (1 << UDF_FLAG_GID_SET);
			break;
		case Opt_uid:
			if (match_int(args, &option))
				return 0;
			uopt->uid = make_kuid(current_user_ns(), option);
			if (!uid_valid(uopt->uid))
				return 0;
			uopt->flags |= (1 << UDF_FLAG_UID_SET);
			break;
		case Opt_umask:
			if (match_octal(args, &option))
				return 0;
			uopt->umask = option;
			break;
		case Opt_nostrict:
			uopt->flags &= ~(1 << UDF_FLAG_STRICT);
			break;
		case Opt_session:
			if (match_int(args, &option))
				return 0;
			uopt->session = option;
			if (!remount)
				uopt->flags |= (1 << UDF_FLAG_SESSION_SET);
			break;
		case Opt_lastblock:
			if (match_int(args, &option))
				return 0;
			uopt->lastblock = option;
			if (!remount)
				uopt->flags |= (1 << UDF_FLAG_LASTBLOCK_SET);
			break;
		case Opt_anchor:
			if (match_int(args, &option))
				return 0;
			uopt->anchor = option;
			break;
		case Opt_volume:
			if (match_int(args, &option))
				return 0;
			uopt->volume = option;
			break;
		case Opt_partition:
			if (match_int(args, &option))
				return 0;
			uopt->partition = option;
			break;
		case Opt_fileset:
			if (match_int(args, &option))
				return 0;
			uopt->fileset = option;
			break;
		case Opt_rootdir:
			if (match_int(args, &option))
				return 0;
			uopt->rootdir = option;
			break;
		case Opt_utf8:
			uopt->flags |= (1 << UDF_FLAG_UTF8);
			break;
#ifdef CONFIG_UDF_NLS
		case Opt_iocharset:
			uopt->nls_map = load_nls(args[0].from);
			uopt->flags |= (1 << UDF_FLAG_NLS_MAP);
			break;
#endif
		case Opt_uignore:
			uopt->flags |= (1 << UDF_FLAG_UID_IGNORE);
			break;
		case Opt_uforget:
			uopt->flags |= (1 << UDF_FLAG_UID_FORGET);
			break;
		case Opt_gignore:
			uopt->flags |= (1 << UDF_FLAG_GID_IGNORE);
			break;
		case Opt_gforget:
			uopt->flags |= (1 << UDF_FLAG_GID_FORGET);
			break;
		case Opt_fmode:
			if (match_octal(args, &option))
				return 0;
			uopt->fmode = option & 0777;
			break;
		case Opt_dmode:
			if (match_octal(args, &option))
				return 0;
			uopt->dmode = option & 0777;
			break;
		default:
			pr_err("bad mount option \"%s\" or missing value\n", p);
			return 0;
		}
