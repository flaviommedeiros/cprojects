#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
if (dbg_wlswemul) {
		tp_features.hotkey_wlsw = 1;
		printk(TPACPI_INFO
			"radio switch emulation enabled\n");
	} else
#endif
	/* Not all thinkpads have a hardware radio switch */
	if (acpi_evalf(hkey_handle, &status, "WLSW", "qd")) {
		tp_features.hotkey_wlsw = 1;
		printk(TPACPI_INFO
			"radio switch found; radios are %s\n",
			enabled(status, 0));
	}
