const struct xattr_handler *v9fs_xattr_handlers[] = {
	&v9fs_xattr_user_handler,
#ifdef CONFIG_9P_FS_POSIX_ACL
	&v9fs_xattr_acl_access_handler,
	&v9fs_xattr_acl_default_handler,
#endif
	NULL
};
