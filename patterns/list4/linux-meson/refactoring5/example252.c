#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
if (dbg_wwanemul) {
		tp_features.wan = 1;
		pr_info("wwan switch emulation enabled\n");
	} else
#endif
	if (tp_features.wan &&
	    !(status & TP_ACPI_WANCARD_HWPRESENT)) {
		/* no wan hardware present in system */
		tp_features.wan = 0;
		dbg_printk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			   "wan hardware not installed\n");
	}
