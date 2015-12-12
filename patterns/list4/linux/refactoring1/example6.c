if (sbi->ll_flags & LL_SBI_RMT_CLIENT) {
		LASSERT(lli->lli_posix_acl == NULL);
		if (lli->lli_remote_perms) {
			free_rmtperm_hash(lli->lli_remote_perms);
			lli->lli_remote_perms = NULL;
		}
	}
#ifdef CONFIG_FS_POSIX_ACL
	else if (lli->lli_posix_acl) {
		LASSERT(atomic_read(&lli->lli_posix_acl->a_refcount) == 1);
		LASSERT(lli->lli_remote_perms == NULL);
		posix_acl_release(lli->lli_posix_acl);
		lli->lli_posix_acl = NULL;
	}
#endif
