if (nh->nh_oif != onh->nh_oif ||
		    nh->nh_gw  != onh->nh_gw ||
		    nh->nh_scope != onh->nh_scope ||
#ifdef CONFIG_IP_ROUTE_MULTIPATH
		    nh->nh_weight != onh->nh_weight ||
#endif
#ifdef CONFIG_NET_CLS_ROUTE
		    nh->nh_tclassid != onh->nh_tclassid ||
#endif
		    ((nh->nh_flags^onh->nh_flags)&~RTNH_F_DEAD))
			return -1;
