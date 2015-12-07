#ifdef RTCONFIG_USB_MODEM
if (dualwan_unit__usbif(wan_unit))
							set_disconn_count(wan_unit, max_disconn_count[wan_unit]);
						else
#endif
							set_disconn_count(wan_unit, S_COUNT);
