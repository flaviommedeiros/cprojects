static struct tlvtype_proc tlvprocdestopt_lst[] = {
#if defined(CONFIG_IPV6_MIP6) || defined(CONFIG_IPV6_MIP6_MODULE)
	{
		.type	= IPV6_TLV_HAO,
		.func	= ipv6_dest_hao,
	},
#endif
	{-1,			NULL}
};
