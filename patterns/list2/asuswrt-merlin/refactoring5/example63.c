#ifdef RTCONFIG_BWDPI
if(nvram_get_int("qos_type") == 1) {
					start_dpi_engine_service();
					// force to rebuild firewall to avoid some loopback issue
					if (nvram_match("fw_nat_loopback", "2"))
						start_firewall(wan_primary_ifunit(), 0);
				}
				else
#endif
				start_iQos();
