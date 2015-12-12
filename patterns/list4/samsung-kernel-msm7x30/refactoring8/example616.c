static int
hash_netiface6_kadt(struct ip_set *set, const struct sk_buff *skb,
		    const struct xt_action_param *par,
		    enum ipset_adt adt, const struct ip_set_adt_opt *opt)
{
	struct ip_set_hash *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	struct hash_netiface6_elem data = {
		.cidr = h->nets[0].cidr ? h->nets[0].cidr : HOST_MASK
	};
	int ret;

	if (data.cidr == 0)
		return -EINVAL;
	if (adt == IPSET_TEST)
		data.cidr = HOST_MASK;

	ip6addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &data.ip.in6);
	ip6_netmask(&data.ip, data.cidr);

	if (opt->cmdflags & IPSET_FLAG_PHYSDEV) {
#ifdef CONFIG_BRIDGE_NETFILTER
		const struct nf_bridge_info *nf_bridge = skb->nf_bridge;

		if (!nf_bridge)
			return -EINVAL;
		data.iface = SRCDIR ? PHYSDEV(physindev) : PHYSDEV(physoutdev);
		data.physdev = 1;
#else
		data.iface = NULL;
#endif
	} else
		data.iface = SRCDIR ? IFACE(in) : IFACE(out);

	if (!data.iface)
		return -EINVAL;
	ret = iface_test(&h->rbtree, &data.iface);
	if (adt == IPSET_ADD) {
		if (!ret) {
			ret = iface_add(&h->rbtree, &data.iface);
			if (ret)
				return ret;
		}
	} else if (!ret)
		return ret;

	return adtfn(set, &data, opt_timeout(opt, h), opt->cmdflags);
}
