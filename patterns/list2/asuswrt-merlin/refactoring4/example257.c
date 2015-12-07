#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,12)
if (nskb->len > dst_mtu(nskb->dst))
#else
	if (nskb->len > dst_pmtu(nskb->dst))
#endif
		goto free_nskb;
