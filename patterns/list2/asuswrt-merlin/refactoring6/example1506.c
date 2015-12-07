if (par->family != NFPROTO_IPV4
#ifdef CONFIG_IP_VS_IPV6
	    && par->family != NFPROTO_IPV6
#endif
		) {
		pr_info("protocol family %u not supported\n", par->family);
		return -EINVAL;
	}
