static const struct nft_set_ops *
nft_select_set_ops(const struct nlattr * const nla[],
		   const struct nft_set_desc *desc,
		   enum nft_set_policies policy)
{
	const struct nft_set_ops *ops, *bops;
	struct nft_set_estimate est, best;
	u32 features;

#ifdef CONFIG_MODULES
	if (list_empty(&nf_tables_set_ops)) {
		nfnl_unlock(NFNL_SUBSYS_NFTABLES);
		request_module("nft-set");
		nfnl_lock(NFNL_SUBSYS_NFTABLES);
		if (!list_empty(&nf_tables_set_ops))
			return ERR_PTR(-EAGAIN);
	}
#endif
	features = 0;
	if (nla[NFTA_SET_FLAGS] != NULL) {
		features = ntohl(nla_get_be32(nla[NFTA_SET_FLAGS]));
		features &= NFT_SET_INTERVAL | NFT_SET_MAP | NFT_SET_TIMEOUT;
	}

	bops	   = NULL;
	best.size  = ~0;
	best.class = ~0;

	list_for_each_entry(ops, &nf_tables_set_ops, list) {
		if ((ops->features & features) != features)
			continue;
		if (!ops->estimate(desc, features, &est))
			continue;

		switch (policy) {
		case NFT_SET_POL_PERFORMANCE:
			if (est.class < best.class)
				break;
			if (est.class == best.class && est.size < best.size)
				break;
			continue;
		case NFT_SET_POL_MEMORY:
			if (est.size < best.size)
				break;
			if (est.size == best.size && est.class < best.class)
				break;
			continue;
		default:
			break;
		}

		if (!try_module_get(ops->owner))
			continue;
		if (bops != NULL)
			module_put(bops->owner);

		bops = ops;
		best = est;
	}

	if (bops != NULL)
		return bops;

	return ERR_PTR(-EOPNOTSUPP);
}
