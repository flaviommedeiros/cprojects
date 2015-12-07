#ifndef RTCONFIG_BCM5301X_TRAFFIC_MONITOR
if(strlen(modelvlan) && strcmp(ifname, "eth0")==0) {
				backup_rx = *rx;
				backup_tx = *tx;
				backup_set  = 1;
			}
			else{
#endif
#ifdef RTCONFIG_DUALWAN
				if ( (unit == wan_primary_ifunit()) || ( !strstr(nvram_safe_get("wans_dualwan"), "none") && nvram_match("wans_mode", "lb")) )
				{
					if (unit == WAN_UNIT_FIRST) {	
						strcpy(ifname_desc, "INTERNET");
						return 1;
					}
					else {
						sprintf(ifname_desc,"INTERNET%d", unit);
						return 1;
					}
				}
#else
				if(unit == wan_primary_ifunit()){
					strcpy(ifname_desc, "INTERNET");
					return 1;
				}			
#endif	/* RTCONFIG_DUALWAN */
#ifndef RTCONFIG_BCM5301X_TRAFFIC_MONITOR
			}
