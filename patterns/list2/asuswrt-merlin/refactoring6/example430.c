if (optname!=MRT_VERSION &&
#ifdef CONFIG_IP_PIMSM
	   optname!=MRT_PIM &&
#endif
	   optname!=MRT_ASSERT)
		return -ENOPROTOOPT;
