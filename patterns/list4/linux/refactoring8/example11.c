static const char * const hibernation_modes[] = {
	[HIBERNATION_PLATFORM]	= "platform",
	[HIBERNATION_SHUTDOWN]	= "shutdown",
	[HIBERNATION_REBOOT]	= "reboot",
#ifdef CONFIG_SUSPEND
	[HIBERNATION_SUSPEND]	= "suspend",
#endif
};
