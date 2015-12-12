static struct attribute *ipw_sysfs_entries[] = {
	&dev_attr_rf_kill.attr,
	&dev_attr_direct_dword.attr,
	&dev_attr_indirect_byte.attr,
	&dev_attr_indirect_dword.attr,
	&dev_attr_mem_gpio_reg.attr,
	&dev_attr_command_event_reg.attr,
	&dev_attr_nic_type.attr,
	&dev_attr_status.attr,
	&dev_attr_cfg.attr,
	&dev_attr_error.attr,
	&dev_attr_event_log.attr,
	&dev_attr_cmd_log.attr,
	&dev_attr_eeprom_delay.attr,
	&dev_attr_ucode_version.attr,
	&dev_attr_rtc.attr,
	&dev_attr_scan_age.attr,
	&dev_attr_led.attr,
	&dev_attr_speed_scan.attr,
	&dev_attr_net_stats.attr,
	&dev_attr_channels.attr,
#ifdef CONFIG_IPW2200_PROMISCUOUS
	&dev_attr_rtap_iface.attr,
	&dev_attr_rtap_filter.attr,
#endif
	NULL
};
