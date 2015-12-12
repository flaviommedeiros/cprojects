#ifdef CONFIG_WIRELESS_CHARGING
if (msm_batt_info.batt_wireless)
				hsusb_chg_vbus_draw_ext(500);	// wireless charging	(450mA)
			else
#endif
				hsusb_chg_vbus_draw_ext(650);
