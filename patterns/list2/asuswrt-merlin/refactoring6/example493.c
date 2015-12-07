if (get_dualwan_by_unit(wan_unit) == WANS_DUALWAN_IF_WAN
#if defined(RTCONFIG_WANRED_LED)
		    || get_dualwan_by_unit(wan_unit) == WANS_DUALWAN_IF_LAN
#endif
		   )
		{
			update_wan_leds(wan_unit);
		}
