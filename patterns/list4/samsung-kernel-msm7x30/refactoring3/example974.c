switch(cmd) {
	case AUTOFS_IOC_READY:	/* Wait queue: go ahead and retry */
		return autofs4_wait_release(sbi,(autofs_wqt_t)arg,0);
	case AUTOFS_IOC_FAIL:	/* Wait queue: fail with ENOENT */
		return autofs4_wait_release(sbi,(autofs_wqt_t)arg,-ENOENT);
	case AUTOFS_IOC_CATATONIC: /* Enter catatonic mode (daemon shutdown) */
		autofs4_catatonic_mode(sbi);
		return 0;
	case AUTOFS_IOC_PROTOVER: /* Get protocol version */
		return autofs4_get_protover(sbi, p);
	case AUTOFS_IOC_PROTOSUBVER: /* Get protocol sub version */
		return autofs4_get_protosubver(sbi, p);
	case AUTOFS_IOC_SETTIMEOUT:
		return autofs4_get_set_timeout(sbi, p);
#ifdef CONFIG_COMPAT
	case AUTOFS_IOC_SETTIMEOUT32:
		return autofs4_compat_get_set_timeout(sbi, p);
#endif

	case AUTOFS_IOC_ASKUMOUNT:
		return autofs4_ask_umount(filp->f_path.mnt, p);

	/* return a single thing to expire */
	case AUTOFS_IOC_EXPIRE:
		return autofs4_expire_run(inode->i_sb,filp->f_path.mnt,sbi, p);
	/* same as above, but can send multiple expires through pipe */
	case AUTOFS_IOC_EXPIRE_MULTI:
		return autofs4_expire_multi(inode->i_sb,filp->f_path.mnt,sbi, p);

	default:
		return -ENOSYS;
	}
