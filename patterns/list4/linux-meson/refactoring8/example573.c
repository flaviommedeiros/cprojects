static int
hash_netiface4_kadt(struct ip_set *set, const struct sk_buff *skb,
		    const struct xt_action_param *par,
		    enum ipset_adt adt, struct ip_set_adt_opt *opt)
{
	struct hash_netiface *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	struct hash_netiface4_elem e = {
		.cidr = h->nets[0].cidr ? h->nets[0].cidr : HOST_MASK,
		.elem = 1,
	};
	struct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, h);
	int ret;

	if (e.cidr == 0)
		return -EINVAL;
	if (adt == IPSET_TEST)
		e.cidr = HOST_MASK;

	ip4addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip);
	e.ip &= ip_set_netmask(e.cidr);

#define IFACE(dir)	(par->dir ? par->dir->name : NULL)
#define PHYSDEV(dir)	(nf_bridge->dir ? nf_bridge->dir->name : NULL)
#define SRCDIR		(opt->flags & IPSET_DIM_TWO_SRC)

	if (opt->cmdflags & IPSET_FLAG_PHYSDEV) {
#ifdef CONFIG_BRIDGE_NETFILTER
		const struct nf_bridge_info *nf_bridge = skb->nf_bridge;

		if (!nf_bridge)
			return -EINVAL;
		e.iface = SRCDIR ? PHYSDEV(physindev) : PHYSDEV(physoutdev);
		e.physdev = 1;
#else
		e.iface = NULL;
#endif
	} else
		e.iface = SRCDIR ? IFACE(in) : IFACE(out);

	if (!e.iface)
		return -EINVAL;
	ret = iface_test(&h->rbtree, &e.iface);
	if (adt == IPSET_ADD) {
		if (!ret) {
			ret = iface_add(&h->rbtree, &e.iface);
			if (ret)
				return ret;
		}
	} else if (!ret)
		return ret;

	return adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
}
