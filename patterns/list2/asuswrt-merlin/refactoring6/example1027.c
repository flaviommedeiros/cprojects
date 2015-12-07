if (nvram_match("dhcp_enable_x", "1") && nvram_match("dnsqmode", "2") 
#ifdef RTCONFIG_DEFAULT_AP_MODE
				&& !nvram_match("ate_flag", "1")
#endif
		) {
			if ((fp = fopen("/etc/dnsmasq.conf", "w+")) != NULL) {
				/* DHCP range */
				char dhcp_start[16], dhcp_end[16], lan_netmask[16];

				strcpy(dhcp_start, nvram_safe_get("dhcp_start"));
				strcpy(dhcp_end, nvram_safe_get("dhcp_end"));
				strcpy(lan_netmask, nvram_safe_get("lan_netmask"));

				if (!chk_valid_startend(lan_ipaddr, dhcp_start, dhcp_end, lan_netmask)) {
					dbg("reset DHCP range: %s ~ %s\n", dhcp_start, dhcp_end);
					nvram_set("dhcp_start", dhcp_start);
					nvram_set("dhcp_end", dhcp_end);
				}

				fprintf(fp, "interface=%s\n", nvram_safe_get("lan_ifname"));
				fprintf(fp, "dhcp-range=lan,%s,%s,%s,%ss\n", 
								dhcp_start, 
								dhcp_end, 
								lan_netmask, 
								nvram_safe_get("dhcp_lease"));
				fprintf(fp, "dhcp-leasefile=/tmp/dnsmasq.leases\n");
				/* Gateway */
				fprintf(fp, "dhcp-option=lan,3,%s\n", lan_ipaddr);
				/* Faster for moving clients, if authoritative */
				fprintf(fp, "dhcp-authoritative\n");
				/* caching */
				fprintf(fp, "cache-size=1500\n"
					    "no-negcache\n");
				fclose(fp);
			}
			else
				perror("/etc/dnsmasq.conf");
		}
		else
			unlink("/etc/dnsmasq.conf");
