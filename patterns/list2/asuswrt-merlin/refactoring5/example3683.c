#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
if (dbg_uwbemul) {
		tp_features.uwb = 1;
		printk(TPACPI_INFO
			"uwb switch emulation enabled\n");
	} else
#endif
	if (tp_features.uwb &&
	    !(status & TP_ACPI_UWB_HWPRESENT)) {
		/* no uwb hardware present in system */
		tp_features.uwb = 0;
		dbg_printk(TPACPI_DBG_INIT,
			   "uwb hardware not installed\n");
	}
