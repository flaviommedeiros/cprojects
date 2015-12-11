switch (vp->magic) {
	case CHECK_SNMP_RSTYPE:
		long_ret = (btype == STATE_RS_SORRY)?2:1;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSADDRTYPE:
		long_ret = (be->addr.ss_family == AF_INET6) ? 2:1;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSADDRESS:
		RETURN_IP46ADDRESS(be);
		break;
	case CHECK_SNMP_RSPORT:
		long_ret = htons(inet_sockaddrport(&be->addr));
		return (u_char *)&long_ret;
	case CHECK_SNMP_RSSTATUS:
		if (btype == STATE_RS_SORRY) break;
		long_ret = be->alive?1:2;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSWEIGHT:
		if (btype == STATE_RS_SORRY) break;
		long_ret = be->weight;
		*write_method = check_snmp_realserver_weight;
		return (u_char*)&long_ret;
#ifdef _KRNL_2_6_
	case CHECK_SNMP_RSUPPERCONNECTIONLIMIT:
		if (btype == STATE_RS_SORRY) break;
		if (!be->u_threshold) break;
		long_ret = be->u_threshold;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSLOWERCONNECTIONLIMIT:
		if (btype == STATE_RS_SORRY) break;
		if (!be->l_threshold) break;
		long_ret = be->l_threshold;
		return (u_char*)&long_ret;
#endif
	case CHECK_SNMP_RSACTIONWHENDOWN:
		if (btype == STATE_RS_SORRY) break;
		long_ret = be->inhibit?2:1;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSNOTIFYUP:
		if (btype == STATE_RS_SORRY) break;
		if (!be->notify_up) break;
		*var_len = strlen(be->notify_up);
		return (u_char*)be->notify_up;
	case CHECK_SNMP_RSNOTIFYDOWN:
		if (btype == STATE_RS_SORRY) break;
		if (!be->notify_down) break;
		*var_len = strlen(be->notify_down);
		return (u_char*)be->notify_down;
	case CHECK_SNMP_RSFAILEDCHECKS:
		if (btype == STATE_RS_SORRY) break;
		if (LIST_ISEMPTY(be->failed_checkers))
			long_ret = 0;
		else
			long_ret = LIST_SIZE(be->failed_checkers);
		return (u_char*)&long_ret;
#if defined(_KRNL_2_6_) && defined(_WITH_LVS_)
	case CHECK_SNMP_RSSTATSCONNS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.conns;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSSTATSACTIVECONNS:
		ipvs_update_stats(bvs);
		long_ret = be->activeconns;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSSTATSINACTIVECONNS:
		ipvs_update_stats(bvs);
		long_ret = be->inactconns;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSSTATSPERSISTENTCONNS:
		ipvs_update_stats(bvs);
		long_ret = be->persistconns;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSSTATSINPKTS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.inpkts;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSSTATSOUTPKTS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.outpkts;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSSTATSINBYTES:
		ipvs_update_stats(bvs);
		counter64_ret.low = be->stats.inbytes & 0xffffffff;
		counter64_ret.high = be->stats.inbytes >> 32;
		*var_len = sizeof(U64);
		return (u_char*)&counter64_ret;
	case CHECK_SNMP_RSSTATSOUTBYTES:
		ipvs_update_stats(bvs);
		counter64_ret.low = be->stats.outbytes & 0xffffffff;
		counter64_ret.high = be->stats.outbytes >> 32;
		*var_len = sizeof(U64);
		return (u_char*)&counter64_ret;
	case CHECK_SNMP_RSRATECPS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.cps;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSRATEINPPS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.inpps;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSRATEOUTPPS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.outpps;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSRATEINBPS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.inbps;
		return (u_char*)&long_ret;
	case CHECK_SNMP_RSRATEOUTBPS:
		ipvs_update_stats(bvs);
		long_ret = be->stats.outbps;
		return (u_char*)&long_ret;
#endif
	default:
		return NULL;
	}
