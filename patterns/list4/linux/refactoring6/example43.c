if (nh->nh_oif != onh->nh_oif ||
		    nh->nh_gw  != onh->nh_gw ||
		    nh->nh_scope != onh->nh_scope ||
#ifdef CONFIG_IP_ROUTE_MULTIPATH
		    nh->nh_weight != onh->nh_weight ||
#endif
#ifdef CONFIG_IP_ROUTE_CLASSID
		    nh->nh_tclassid != onh->nh_tclassid ||
#endif
		    lwtunnel_cmp_encap(nh->nh_lwtstate, onh->nh_lwtstate) ||
		    ((nh->nh_flags ^ onh->nh_flags) & ~RTNH_COMPARE_MASK))
			return -1;
