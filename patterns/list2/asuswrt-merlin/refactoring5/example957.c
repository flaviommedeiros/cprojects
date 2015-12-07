#ifdef CONFIG_REISERFS_FS_POSIX_ACL
if (REISERFS_I(dir)->i_acl_default && !IS_ERR(REISERFS_I(dir)->i_acl_default)) {
		reiserfs_write_unlock_xattrs(dir->i_sb);
		iput(inode);
		reiserfs_write_lock_xattrs(dir->i_sb);
	} else
#endif
		iput(inode);
