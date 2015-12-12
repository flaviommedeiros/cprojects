static struct nf_hook_ops ip_vs_ops[] __read_mostly = {
	/* After packet filtering, forward packet through VS/DR, VS/TUN,
	 * or VS/NAT(change destination), so that filtering rules can be
	 * applied to IPVS. */
	{
		.hook		= ip_vs_in,
		.owner		= THIS_MODULE,
		.pf		= PF_INET,
		.hooknum        = NF_INET_LOCAL_IN,
		.priority       = 100,
	},
	/* After packet filtering, change source only for VS/NAT */
	{
		.hook		= ip_vs_out,
		.owner		= THIS_MODULE,
		.pf		= PF_INET,
		.hooknum        = NF_INET_FORWARD,
		.priority       = 100,
	},
	/* After packet filtering (but before ip_vs_out_icmp), catch icmp
	 * destined for 0.0.0.0/0, which is for incoming IPVS connections */
	{
		.hook		= ip_vs_forward_icmp,
		.owner		= THIS_MODULE,
		.pf		= PF_INET,
		.hooknum        = NF_INET_FORWARD,
		.priority       = 99,
	},
	/* Before the netfilter connection tracking, exit from POST_ROUTING */
	{
		.hook		= ip_vs_post_routing,
		.owner		= THIS_MODULE,
		.pf		= PF_INET,
		.hooknum        = NF_INET_POST_ROUTING,
		.priority       = NF_IP_PRI_NAT_SRC-1,
	},
#ifdef CONFIG_IP_VS_IPV6
	/* After packet filtering, forward packet through VS/DR, VS/TUN,
	 * or VS/NAT(change destination), so that filtering rules can be
	 * applied to IPVS. */
	{
		.hook		= ip_vs_in,
		.owner		= THIS_MODULE,
		.pf		= PF_INET6,
		.hooknum        = NF_INET_LOCAL_IN,
		.priority       = 100,
	},
	/* After packet filtering, change source only for VS/NAT */
	{
		.hook		= ip_vs_out,
		.owner		= THIS_MODULE,
		.pf		= PF_INET6,
		.hooknum        = NF_INET_FORWARD,
		.priority       = 100,
	},
	/* After packet filtering (but before ip_vs_out_icmp), catch icmp
	 * destined for 0.0.0.0/0, which is for incoming IPVS connections */
	{
		.hook		= ip_vs_forward_icmp_v6,
		.owner		= THIS_MODULE,
		.pf		= PF_INET6,
		.hooknum        = NF_INET_FORWARD,
		.priority       = 99,
	},
	/* Before the netfilter connection tracking, exit from POST_ROUTING */
	{
		.hook		= ip_vs_post_routing,
		.owner		= THIS_MODULE,
		.pf		= PF_INET6,
		.hooknum        = NF_INET_POST_ROUTING,
		.priority       = NF_IP6_PRI_NAT_SRC-1,
	},
#endif
};
