const struct xattr_handler *f2fs_xattr_handlers[] = {
	&f2fs_xattr_user_handler,
#ifdef CONFIG_F2FS_FS_POSIX_ACL
	&f2fs_xattr_acl_access_handler,
	&f2fs_xattr_acl_default_handler,
#endif
	&f2fs_xattr_trusted_handler,
	&f2fs_xattr_advise_handler,
	NULL,
};
