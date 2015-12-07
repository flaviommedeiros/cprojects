if (
#if defined(RTCONFIG_USB_MODEM)
		    dualwan_unit__nonusbif(unit) &&
#endif
		    !nvram_match("ipv6_ifdev", "ppp"))
			break;
