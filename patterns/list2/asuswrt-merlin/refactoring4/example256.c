#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
if (ip_route_output_key(&init_net, &nrt, &fl))
#else
	if (ip_route_output_key(&nrt, &fl))
#endif
		goto free_nskb;
