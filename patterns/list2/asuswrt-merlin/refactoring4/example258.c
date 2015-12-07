#if defined(CONFIG_NET_IPGRE_DEMUX) || defined(CONFIG_NET_IPGRE_DEMUX_MODULE)
if (gre_del_protocol(&ipgre_protocol, GREPROTO_CISCO) < 0)
#else
	if (inet_del_protocol(&ipgre_protocol, IPPROTO_GRE) < 0)
#endif
		printk(KERN_INFO "ipgre close: can't remove protocol\n");
