static const struct xattr_handler *f2fs_xattr_handler_map[] = {
	[F2FS_XATTR_INDEX_USER] = &f2fs_xattr_user_handler,
#ifdef CONFIG_F2FS_FS_POSIX_ACL
	[F2FS_XATTR_INDEX_POSIX_ACL_ACCESS] = &f2fs_xattr_acl_access_handler,
	[F2FS_XATTR_INDEX_POSIX_ACL_DEFAULT] = &f2fs_xattr_acl_default_handler,
#endif
	[F2FS_XATTR_INDEX_TRUSTED] = &f2fs_xattr_trusted_handler,
	[F2FS_XATTR_INDEX_ADVISE] = &f2fs_xattr_advise_handler,
};
