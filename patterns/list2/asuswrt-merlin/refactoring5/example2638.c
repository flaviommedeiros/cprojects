#ifdef CONFIG_BCMWL5
if (wlconf(ifname, unit, subunit) == 0) {
					const char *mode = nvram_safe_get(wl_nvname("mode", unit, subunit));

					if (strcmp(mode, "wet") == 0) {
						// Enable host DHCP relay
						if (nvram_match("lan_proto", "static")) {
#ifdef __CONFIG_DHDAP__
							is_dhd = !dhd_probe(ifname);
							if(is_dhd) {
								char macbuf[sizeof("wet_host_mac") + 1 + ETHER_ADDR_LEN];
								dhd_iovar_setbuf(ifname, "wet_host_mac", ifr.ifr_hwaddr.sa_data, ETHER_ADDR_LEN , macbuf, sizeof(macbuf));
							}
							else
#endif /* __CONFIG_DHDAP__ */
							wl_iovar_set(ifname, "wet_host_mac", ifr.ifr_hwaddr.sa_data, ETHER_ADDR_LEN);
						}
					}

					sta |= (strcmp(mode, "sta") == 0);
					if ((strcmp(mode, "ap") != 0) && (strcmp(mode, "wet") != 0)
						&& (strcmp(mode, "psta") != 0) && (strcmp(mode, "psr") != 0))
						continue;
				}
