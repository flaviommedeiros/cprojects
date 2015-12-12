switch (token) {
	case Opt_snapdirname:
		kfree(fsopt->snapdir_name);
		fsopt->snapdir_name = kstrndup(argstr[0].from,
					       argstr[0].to-argstr[0].from,
					       GFP_KERNEL);
		if (!fsopt->snapdir_name)
			return -ENOMEM;
		break;

		/* misc */
	case Opt_wsize:
		fsopt->wsize = intval;
		break;
	case Opt_rsize:
		fsopt->rsize = intval;
		break;
	case Opt_rasize:
		fsopt->rasize = intval;
		break;
	case Opt_caps_wanted_delay_min:
		fsopt->caps_wanted_delay_min = intval;
		break;
	case Opt_caps_wanted_delay_max:
		fsopt->caps_wanted_delay_max = intval;
		break;
	case Opt_readdir_max_entries:
		fsopt->max_readdir = intval;
		break;
	case Opt_readdir_max_bytes:
		fsopt->max_readdir_bytes = intval;
		break;
	case Opt_congestion_kb:
		fsopt->congestion_kb = intval;
		break;
	case Opt_dirstat:
		fsopt->flags |= CEPH_MOUNT_OPT_DIRSTAT;
		break;
	case Opt_nodirstat:
		fsopt->flags &= ~CEPH_MOUNT_OPT_DIRSTAT;
		break;
	case Opt_rbytes:
		fsopt->flags |= CEPH_MOUNT_OPT_RBYTES;
		break;
	case Opt_norbytes:
		fsopt->flags &= ~CEPH_MOUNT_OPT_RBYTES;
		break;
	case Opt_asyncreaddir:
		fsopt->flags &= ~CEPH_MOUNT_OPT_NOASYNCREADDIR;
		break;
	case Opt_noasyncreaddir:
		fsopt->flags |= CEPH_MOUNT_OPT_NOASYNCREADDIR;
		break;
	case Opt_dcache:
		fsopt->flags |= CEPH_MOUNT_OPT_DCACHE;
		break;
	case Opt_nodcache:
		fsopt->flags &= ~CEPH_MOUNT_OPT_DCACHE;
		break;
	case Opt_ino32:
		fsopt->flags |= CEPH_MOUNT_OPT_INO32;
		break;
	case Opt_noino32:
		fsopt->flags &= ~CEPH_MOUNT_OPT_INO32;
		break;
	case Opt_fscache:
		fsopt->flags |= CEPH_MOUNT_OPT_FSCACHE;
		break;
	case Opt_nofscache:
		fsopt->flags &= ~CEPH_MOUNT_OPT_FSCACHE;
		break;
	case Opt_poolperm:
		fsopt->flags &= ~CEPH_MOUNT_OPT_NOPOOLPERM;
		printk ("pool perm");
		break;
	case Opt_nopoolperm:
		fsopt->flags |= CEPH_MOUNT_OPT_NOPOOLPERM;
		break;
#ifdef CONFIG_CEPH_FS_POSIX_ACL
	case Opt_acl:
		fsopt->sb_flags |= MS_POSIXACL;
		break;
#endif
	case Opt_noacl:
		fsopt->sb_flags &= ~MS_POSIXACL;
		break;
	default:
		BUG_ON(token);
	}
