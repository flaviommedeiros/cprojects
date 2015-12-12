static struct ac97_quirk ac97_quirks[] __devinitdata = {
#if 0 /* Not yet confirmed if all 5536 boards are HP only */
	{
		.subvendor = PCI_VENDOR_ID_AMD, 
		.subdevice = PCI_DEVICE_ID_AMD_CS5536_AUDIO, 
		.name = "AMD RDK",     
		.type = AC97_TUNE_HP_ONLY
	},
#endif
	{}
};
