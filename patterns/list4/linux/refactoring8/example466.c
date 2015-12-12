const struct xattr_handler *hfsplus_xattr_handlers[] = {
	&hfsplus_xattr_osx_handler,
	&hfsplus_xattr_user_handler,
	&hfsplus_xattr_trusted_handler,
#ifdef CONFIG_HFSPLUS_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_default_xattr_handler,
#endif
	&hfsplus_xattr_security_handler,
	NULL
};
