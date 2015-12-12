const struct xattr_handler *btrfs_xattr_handlers[] = {
#ifdef CONFIG_BTRFS_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_default_xattr_handler,
#endif
	NULL,
};
