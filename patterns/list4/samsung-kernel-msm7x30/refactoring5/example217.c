#ifdef CONFIG_THINKPAD_ACPI_DEBUGFACILITIES
if (dbg_wlswemul) {
		tp_features.hotkey_wlsw = 1;
		radiosw_state = !!tpacpi_wlsw_emulstate;
		pr_info("radio switch emulation enabled\n");
	} else
#endif
	/* Not all thinkpads have a hardware radio switch */
	if (acpi_evalf(hkey_handle, &status, "WLSW", "qd")) {
		tp_features.hotkey_wlsw = 1;
		radiosw_state = !!status;
		pr_info("radio switch found; radios are %s\n",
			enabled(status, 0));
	}
