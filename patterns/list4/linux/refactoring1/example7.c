if (sbi->ll_flags & LL_SBI_RMT_CLIENT) {
		if (body->valid & OBD_MD_FLRMTPERM)
			ll_update_remote_perm(inode, md->remote_perm);
	}
#ifdef CONFIG_FS_POSIX_ACL
	else if (body->valid & OBD_MD_FLACL) {
		spin_lock(&lli->lli_lock);
		if (lli->lli_posix_acl)
			posix_acl_release(lli->lli_posix_acl);
		lli->lli_posix_acl = md->posix_acl;
		spin_unlock(&lli->lli_lock);
	}
#endif
