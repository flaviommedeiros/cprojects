static const struct tlvtype_proc tlvprocdestopt_lst[] = {
#if IS_ENABLED(CONFIG_IPV6_MIP6)
	{
		.type	= IPV6_TLV_HAO,
		.func	= ipv6_dest_hao,
	},
#endif
	{-1,			NULL}
};
