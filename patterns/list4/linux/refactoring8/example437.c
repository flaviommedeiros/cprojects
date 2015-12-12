static int
hash_netiface6_kadt(struct ip_set *set, const struct sk_buff *skb,
		    const struct xt_action_param *par,
		    enum ipset_adt adt, struct ip_set_adt_opt *opt)
{
	struct hash_netiface *h = set->data;
	ipset_adtfn adtfn = set->variant->adt[adt];
	struct hash_netiface6_elem e = {
		.cidr = INIT_CIDR(h->nets[0].cidr[0], HOST_MASK),
		.elem = 1,
	};
	struct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (e.cidr == 0)
		return -EINVAL;
	if (adt == IPSET_TEST)
		e.cidr = HOST_MASK;

	ip6addrptr(skb, opt->flags & IPSET_DIM_ONE_SRC, &e.ip.in6);
	ip6_netmask(&e.ip, e.cidr);

	if (opt->cmdflags & IPSET_FLAG_PHYSDEV) {
#if IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
		const char *eiface = SRCDIR ? get_physindev_name(skb) :
					      get_physoutdev_name(skb);

		if (!eiface)
			return -EINVAL;
		STRLCPY(e.iface, eiface);
		e.physdev = 1;
#endif
	} else {
		STRLCPY(e.iface, SRCDIR ? IFACE(in) : IFACE(out));
	}

	if (strlen(e.iface) == 0)
		return -EINVAL;

	return adtfn(set, &e, &ext, &opt->ext, opt->cmdflags);
}
