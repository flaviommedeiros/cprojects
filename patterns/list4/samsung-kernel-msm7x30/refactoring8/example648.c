const struct xattr_handler *xfs_xattr_handlers[] = {
	&xfs_xattr_user_handler,
	&xfs_xattr_trusted_handler,
	&xfs_xattr_security_handler,
#ifdef CONFIG_XFS_POSIX_ACL
	&xfs_xattr_acl_access_handler,
	&xfs_xattr_acl_default_handler,
#endif
	NULL
};
