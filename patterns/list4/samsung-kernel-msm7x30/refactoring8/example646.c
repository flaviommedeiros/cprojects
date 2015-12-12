static const struct rpc_version	*nlm_versions[] = {
	[1] = &nlm_version1,
	[3] = &nlm_version3,
#ifdef CONFIG_LOCKD_V4
	[4] = &nlm_version4,
#endif
};
