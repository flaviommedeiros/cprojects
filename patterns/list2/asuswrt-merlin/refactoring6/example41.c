if(!strcmp(wan_proto, "dhcp")
#ifdef RTCONFIG_WIRELESSREPEATER
					|| sw_mode == SW_MODE_HOTSPOT
#endif
					)
				logmessage(log_title, "ISP's DHCP did not function properly.");
