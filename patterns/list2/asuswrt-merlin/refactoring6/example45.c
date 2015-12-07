if(get_dualwan_by_unit(other_wan_unit) != WANS_DUALWAN_IF_NONE
					&& (get_disconn_count(current_wan_unit) >= max_disconn_count[current_wan_unit]
#ifdef RTCONFIG_USB_MODEM
							|| (!link_wan[current_wan_unit] && dualwan_unit__usbif(current_wan_unit)
#ifdef RTCONFIG_INTERNAL_GOBI
									&& strcmp(usb_if, "")
#endif
									)
#endif
							)
					)
			{
				csprintf("# wanduck(%d): Switching the connect to the %d WAN line...\n", current_wan_unit, get_next_unit(current_wan_unit));
				if(!link_wan[current_wan_unit] && dualwan_unit__usbif(current_wan_unit))
					switch_wan_line(other_wan_unit, 0);
				else
					switch_wan_line(other_wan_unit, 1);
			}
