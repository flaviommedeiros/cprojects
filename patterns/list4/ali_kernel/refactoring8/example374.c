static struct xattr_handler *ocfs2_xattr_handler_map[OCFS2_XATTR_MAX] = {
	[OCFS2_XATTR_INDEX_USER]	= &ocfs2_xattr_user_handler,
#ifdef CONFIG_OCFS2_FS_POSIX_ACL
	[OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS]
					= &ocfs2_xattr_acl_access_handler,
	[OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT]
					= &ocfs2_xattr_acl_default_handler,
#endif
	[OCFS2_XATTR_INDEX_TRUSTED]	= &ocfs2_xattr_trusted_handler,
	[OCFS2_XATTR_INDEX_SECURITY]	= &ocfs2_xattr_security_handler,
};
