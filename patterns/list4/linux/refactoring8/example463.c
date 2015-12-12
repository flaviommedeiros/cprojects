const struct xattr_handler *nfs4_xattr_handlers[] = {
	&nfs4_xattr_nfs4_acl_handler,
#ifdef CONFIG_NFS_V4_SECURITY_LABEL
	&nfs4_xattr_nfs4_label_handler,
#endif
	NULL
};
