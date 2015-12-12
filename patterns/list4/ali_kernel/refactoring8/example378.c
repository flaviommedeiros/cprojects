const struct nfs4_minor_version_ops *nfs_v4_minor_ops[] = {
	[0] = &nfs_v4_0_minor_ops,
#if defined(CONFIG_NFS_V4_1)
	[1] = &nfs_v4_1_minor_ops,
#endif
};
