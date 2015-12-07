#ifdef RTCONFIG_BCMWL6
if (!psta_exist_except(unit)/* || !psr_exist_except(unit)*/)
#endif
#endif
			{
#ifdef RTCONFIG_QTN
				if (strcmp(ifname, "wifi0"))
#endif
				eval("wlconf", ifname, "start"); /* start wl iface */
			}
