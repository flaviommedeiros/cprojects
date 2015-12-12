struct xattr_handler *btrfs_xattr_handlers[] = {
#ifdef CONFIG_BTRFS_FS_POSIX_ACL
	&btrfs_xattr_acl_access_handler,
	&btrfs_xattr_acl_default_handler,
#endif
	NULL,
};
