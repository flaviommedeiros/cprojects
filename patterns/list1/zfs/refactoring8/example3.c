xattr_handler_t *zpl_xattr_handlers[] = {
	&zpl_xattr_security_handler,
	&zpl_xattr_trusted_handler,
	&zpl_xattr_user_handler,
#ifdef CONFIG_FS_POSIX_ACL
	&zpl_xattr_acl_access_handler,
	&zpl_xattr_acl_default_handler,
#endif /* CONFIG_FS_POSIX_ACL */
	NULL
};
