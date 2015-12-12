static struct bfin_phydev_platform_data bfin_phydev_data[] = {
	{
#if defined(CONFIG_NET_DSA_KSZ8893M) || defined(CONFIG_NET_DSA_KSZ8893M_MODULE)
		.addr = 3,
#else
		.addr = 1,
#endif
		.irq = IRQ_MAC_PHYINT,
	},
};
