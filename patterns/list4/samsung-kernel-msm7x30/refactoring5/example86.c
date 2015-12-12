#ifdef CONFIG_WIRELESS_CHARGING
if (msm_batt_info.batt_wireless)
				hsusb_chg_vbus_draw_ext(500);	// wireless charging	(450mA)
			else
#endif

			if (board_hw_revision >= CONFIG_HW_REV_USING_SMB328)
				val_chg_current.intval = 600;
			else
				hsusb_chg_vbus_draw_ext(650);
