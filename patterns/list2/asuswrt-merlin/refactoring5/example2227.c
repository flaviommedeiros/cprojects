#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
if (dbg_bluetoothemul) {
		tp_features.bluetooth = 1;
		printk(TPACPI_INFO
			"bluetooth switch emulation enabled\n");
	} else
#endif
	if (tp_features.bluetooth &&
	    !(status & TP_ACPI_BLUETOOTH_HWPRESENT)) {
		/* no bluetooth hardware present in system */
		tp_features.bluetooth = 0;
		dbg_printk(TPACPI_DBG_INIT | TPACPI_DBG_RFKILL,
			   "bluetooth hardware not installed\n");
	}
