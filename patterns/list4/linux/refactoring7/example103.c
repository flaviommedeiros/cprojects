return nla_total_size(1)	/* IFLA_BRPORT_STATE  */
		+ nla_total_size(2)	/* IFLA_BRPORT_PRIORITY */
		+ nla_total_size(4)	/* IFLA_BRPORT_COST */
		+ nla_total_size(1)	/* IFLA_BRPORT_MODE */
		+ nla_total_size(1)	/* IFLA_BRPORT_GUARD */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROTECT */
		+ nla_total_size(1)	/* IFLA_BRPORT_FAST_LEAVE */
		+ nla_total_size(1)	/* IFLA_BRPORT_LEARNING */
		+ nla_total_size(1)	/* IFLA_BRPORT_UNICAST_FLOOD */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROXYARP */
		+ nla_total_size(1)	/* IFLA_BRPORT_PROXYARP_WIFI */
		+ nla_total_size(sizeof(struct ifla_bridge_id))	/* IFLA_BRPORT_ROOT_ID */
		+ nla_total_size(sizeof(struct ifla_bridge_id))	/* IFLA_BRPORT_BRIDGE_ID */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_DESIGNATED_PORT */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_DESIGNATED_COST */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_ID */
		+ nla_total_size(sizeof(u16))	/* IFLA_BRPORT_NO */
		+ nla_total_size(sizeof(u8))	/* IFLA_BRPORT_TOPOLOGY_CHANGE_ACK */
		+ nla_total_size(sizeof(u8))	/* IFLA_BRPORT_CONFIG_PENDING */
		+ nla_total_size(sizeof(u64))	/* IFLA_BRPORT_MESSAGE_AGE_TIMER */
		+ nla_total_size(sizeof(u64))	/* IFLA_BRPORT_FORWARD_DELAY_TIMER */
		+ nla_total_size(sizeof(u64))	/* IFLA_BRPORT_HOLD_TIMER */
#ifdef CONFIG_BRIDGE_IGMP_SNOOPING
		+ nla_total_size(sizeof(u8))	/* IFLA_BRPORT_MULTICAST_ROUTER */
#endif
		+ 0;
