#ifdef CONFIG_RTC_HCTOSYS_DEVICE
if (strcmp(dev_name(&to_rtc_device(dev)->dev),
		   CONFIG_RTC_HCTOSYS_DEVICE) == 0)
		return sprintf(buf, "1\n");
	else
#endif
		return sprintf(buf, "0\n");
