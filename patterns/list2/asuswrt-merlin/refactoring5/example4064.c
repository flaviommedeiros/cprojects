#ifdef RTCONFIG_DUALWAN
if(nvram_match("wans_mode", "lb") && gate_num > 1){
			if(strlen(wan_ip) <= 0 || !strcmp(wan_ip, "0.0.0.0"))
				continue;

			if(unit == WAN_UNIT_SECOND)
				table = WAN1_ROUTE_TABLE;
			else
				table = WAN0_ROUTE_TABLE;

			// set the rules of wan[X]'s ip and gateway for multi routing tables.
			snprintf(cmd2, 2048, "ip rule del pref 200 from %s table %d", wan_ip, table);
			system(cmd2);

			snprintf(cmd2, 2048, "ip rule add pref 200 from %s table %d", wan_ip, table);
			system(cmd2);

			snprintf(cmd2, 2048, "ip rule del pref 400 to %s table %d", wan_gate, table);
			system(cmd2);

			snprintf(cmd2, 2048, "ip rule add pref 400 to %s table %d", wan_gate, table);
			system(cmd2);

			// set the routes for multi routing tables.
			copy_routes(table);

			if(!strcmp(wan_proto, "pptp") || !strcmp(wan_proto, "l2tp")){
				snprintf(cmd2, 2048, "ip route add %s dev %s table %d", wan_gate, wan_if, table);
				system(cmd2);
			}

			snprintf(cmd2, 2048, "ip route replace default via %s dev %s table %d", wan_gate, wan_if, table);
			system(cmd2);

			if(!strcmp(wan_proto, "pptp") || !strcmp(wan_proto, "l2tp")){
				snprintf(cmd2, 2048, "ip route del %s dev %s table %d", wan_gate, wan_if, table);
				system(cmd2);
			}

			strcpy(wan_multi_if[unit], wan_if);
			strcpy(wan_multi_gate[unit], wan_gate);

			// set the static routing rules.
			if(nvram_match("wans_routing_enable", "1")){
				char *rfrom, *rto, *rtable_str;
				int rtable;

				nvp = nv = strdup(nvram_safe_get("wans_routing_rulelist"));
				while(nv && (b = strsep(&nvp, "<")) != NULL){
					if((vstrsep(b, ">", &rfrom, &rto, &rtable_str) != 3))
						continue;

					if(!strcmp(rfrom, "all") && !strcmp(rfrom, rto))
						continue;

					rtable = atoi(rtable_str);

					if(rtable == WAN_UNIT_FIRST || rtable == WAN0_ROUTE_TABLE)
						rtable = WAN0_ROUTE_TABLE;
					else if(rtable == WAN_UNIT_SECOND || rtable == WAN1_ROUTE_TABLE)
						rtable = WAN1_ROUTE_TABLE;
					else // incorrect table.
						continue;

					if(rtable == table){
						snprintf(cmd2, 2048, "ip rule del pref 100 from %s to %s table %d", rfrom, rto, rtable);
						system(cmd2);

						snprintf(cmd2, 2048, "ip rule add pref 100 from %s to %s table %d", rfrom, rto, rtable);
						system(cmd2);
					}
	 			}
				free(nv);
			}

			// ISP's routing rules.
			if(nvram_match(strcat_r(prefix, "routing_isp_enable", tmp), "1")){
				strncpy(wan_isp, nvram_safe_get(strcat_r(prefix, "routing_isp", tmp)), 32);

				FILE *fp;
				char conf_name[64], line[1024];

				snprintf(conf_name, 64, "/rom/etc/static_routes/%s.conf", wan_isp);

				if((fp = fopen(conf_name, "r")) != NULL){
					while(fgets(line, sizeof(line), fp)){
						char *token = strtok(line, "\n");

						snprintf(cmd2, 2048, "ip rule del pref 300 %s table %d", token, table);
						system(cmd2);

						snprintf(cmd2, 2048, "ip rule add pref 300 %s table %d", token, table);
						system(cmd2);
					}
					fclose(fp);
				}
			}
		}
		else
#endif
		{
			if(!strcmp(wan_proto, "pptp") || !strcmp(wan_proto, "l2tp")){
				snprintf(cmd, 2048, "ip route add %s dev %s", wan_gate, wan_if);
				system(cmd);
			}

			// set the default gateway.
			snprintf(cmd, 2048, "ip route replace default via %s dev %s", wan_gate, wan_if);
			system(cmd);

			if(!strcmp(wan_proto, "pptp") || !strcmp(wan_proto, "l2tp")){
				snprintf(cmd, 2048, "ip route del %s dev %s", wan_gate, wan_if);
				system(cmd);
			}
		}
