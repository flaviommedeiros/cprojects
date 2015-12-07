if(strcmp(wanx_if, wan_if) && inet_addr_(wanx_ip)
#ifdef RTCONFIG_DUALWAN
			&& dualwan_unit__nonusbif(unit)
#endif
			)
		fprintf(fp, "-A FORWARD -o %s ! -i %s -j %s\n", wanx_if, lan_if, logdrop);
