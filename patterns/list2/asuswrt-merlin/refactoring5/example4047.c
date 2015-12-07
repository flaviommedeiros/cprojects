#ifdef RTCONFIG_DHCP_OVERRIDE
if (nvram_match("dnsqmode", "2")) {
			disconn_case[wan_unit] = CASE_DISWAN;
			return DISCONN;
		}
		else
#endif
		return CONNED;
