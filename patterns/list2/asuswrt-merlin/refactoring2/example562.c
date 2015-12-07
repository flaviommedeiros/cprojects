#ifdef CONFIG_BCMWL5
if (strcmp(ifname, "wifi0"))
#endif
				{
					eval("wlconf", ifname, "down");
					eval("wl", "-i", ifname, "radio", "off");
					ifconfig(ifname, 0, NULL, NULL);
				}
