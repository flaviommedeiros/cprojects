static struct attribute *hotkey_attributes[] __initdata = {
	&dev_attr_hotkey_enable.attr,
	&dev_attr_hotkey_bios_enabled.attr,
	&dev_attr_hotkey_bios_mask.attr,
	&dev_attr_hotkey_report_mode.attr,
	&dev_attr_hotkey_wakeup_reason.attr,
	&dev_attr_hotkey_wakeup_hotunplug_complete.attr,
	&dev_attr_hotkey_mask.attr,
	&dev_attr_hotkey_all_mask.attr,
	&dev_attr_hotkey_recommended_mask.attr,
#ifdef CONFIG_THINKPAD_ACPI_HOTKEY_POLL
	&dev_attr_hotkey_source_mask.attr,
	&dev_attr_hotkey_poll_freq.attr,
#endif
};
