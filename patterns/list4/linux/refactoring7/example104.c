return nla_total_size(sizeof(u32)) +	/* IFLA_BR_FORWARD_DELAY  */
	       nla_total_size(sizeof(u32)) +	/* IFLA_BR_HELLO_TIME */
	       nla_total_size(sizeof(u32)) +	/* IFLA_BR_MAX_AGE */
	       nla_total_size(sizeof(u32)) +    /* IFLA_BR_AGEING_TIME */
	       nla_total_size(sizeof(u32)) +    /* IFLA_BR_STP_STATE */
	       nla_total_size(sizeof(u16)) +    /* IFLA_BR_PRIORITY */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_VLAN_FILTERING */
#ifdef CONFIG_BRIDGE_VLAN_FILTERING
	       nla_total_size(sizeof(__be16)) +	/* IFLA_BR_VLAN_PROTOCOL */
	       nla_total_size(sizeof(u16)) +    /* IFLA_BR_VLAN_DEFAULT_PVID */
#endif
	       nla_total_size(sizeof(u16)) +    /* IFLA_BR_GROUP_FWD_MASK */
	       nla_total_size(sizeof(struct ifla_bridge_id)) +   /* IFLA_BR_ROOT_ID */
	       nla_total_size(sizeof(struct ifla_bridge_id)) +   /* IFLA_BR_BRIDGE_ID */
	       nla_total_size(sizeof(u16)) +    /* IFLA_BR_ROOT_PORT */
	       nla_total_size(sizeof(u32)) +    /* IFLA_BR_ROOT_PATH_COST */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_TOPOLOGY_CHANGE */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_TOPOLOGY_CHANGE_DETECTED */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_HELLO_TIMER */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_TCN_TIMER */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_TOPOLOGY_CHANGE_TIMER */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_GC_TIMER */
	       nla_total_size(ETH_ALEN) +       /* IFLA_BR_GROUP_ADDR */
#ifdef CONFIG_BRIDGE_IGMP_SNOOPING
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_MCAST_ROUTER */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_MCAST_SNOOPING */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_MCAST_QUERY_USE_IFADDR */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_MCAST_QUERIER */
	       nla_total_size(sizeof(u32)) +    /* IFLA_BR_MCAST_HASH_ELASTICITY */
	       nla_total_size(sizeof(u32)) +    /* IFLA_BR_MCAST_HASH_MAX */
	       nla_total_size(sizeof(u32)) +    /* IFLA_BR_MCAST_LAST_MEMBER_CNT */
	       nla_total_size(sizeof(u32)) +    /* IFLA_BR_MCAST_STARTUP_QUERY_CNT */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_MCAST_LAST_MEMBER_INTVL */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_MCAST_MEMBERSHIP_INTVL */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_MCAST_QUERIER_INTVL */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_MCAST_QUERY_INTVL */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_MCAST_QUERY_RESPONSE_INTVL */
	       nla_total_size(sizeof(u64)) +    /* IFLA_BR_MCAST_STARTUP_QUERY_INTVL */
#endif
#if IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_NF_CALL_IPTABLES */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_NF_CALL_IP6TABLES */
	       nla_total_size(sizeof(u8)) +     /* IFLA_BR_NF_CALL_ARPTABLES */
#endif
	       0;
