#if defined(CONFIG_MACH_APACHE)
if ((dev1 == CRA_USB) || (dev1 == CRA_USB_CHARGER) || (dev1==0 && dev2==CRB_JIG_USB_OFF))
#else
	if ((dev1 == CRA_USB) || (dev1 == CRA_USB_CHARGER))
#endif
	{
		curr_usb_status = 1;

		usb_switch_state(); // re-enable HUB_EN if it should be on
			
		pr_info("[FSA9480] %s: USB connected...\n", __func__);
	}
	else	// consider as dedicated charger any device with vbus power
	{
		curr_ta_status = 1;
		pr_info("[FSA9480] %s: TA connected...\n", __func__);
	}
