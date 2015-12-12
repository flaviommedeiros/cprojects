static DevinfoDevHandler *devinfo_handlers[] = {
	&devinfo_computer_handler,
	&devinfo_cpu_handler,
	&devinfo_optical_handler,
#if notyet
	&devinfo_scsipi_handler,
	&devinfo_ide_handler,
	&devinfo_scsi_handler,
	&devinfo_floppy_handler,
	&devinfo_usb_handler,
	&devinfo_pci_handler,
	&devinfo_lofi_handler,
#endif
	&devinfo_audio_handler,
	&devinfo_audio_mixer_handler,
	&devinfo_audio_dsp_handler,
	&devinfo_video_handler,
	&devinfo_mass_handler,
	&devinfo_default_handler,
	NULL
};
