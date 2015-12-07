#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,21)
if (xt_register_target(&ip6t_route_reg))
#else
	if (ip6t_register_target(&ip6t_route_reg))
#endif
		return -EINVAL;
