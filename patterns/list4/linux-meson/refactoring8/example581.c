static const struct xattr_handler *shmem_xattr_handlers[] = {
#ifdef CONFIG_TMPFS_POSIX_ACL
	&generic_acl_access_handler,
	&generic_acl_default_handler,
#endif
	NULL
};
