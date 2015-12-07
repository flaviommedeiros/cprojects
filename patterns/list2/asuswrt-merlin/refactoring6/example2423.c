if(unit != wan_primary_ifunit()
#ifdef RTCONFIG_DUALWAN
				&& !nvram_match("wans_mode", "lb")
#endif
				)
			continue;
