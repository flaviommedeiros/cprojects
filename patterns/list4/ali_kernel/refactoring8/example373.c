struct xattr_handler *ocfs2_xattr_handlers[] = {
	&ocfs2_xattr_user_handler,
#ifdef CONFIG_OCFS2_FS_POSIX_ACL
	&ocfs2_xattr_acl_access_handler,
	&ocfs2_xattr_acl_default_handler,
#endif
	&ocfs2_xattr_trusted_handler,
	&ocfs2_xattr_security_handler,
	NULL
};
