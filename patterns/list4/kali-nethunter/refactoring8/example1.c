static struct android_usb_function *supported_functions[] = {
	&mbim_function,
	&ecm_qc_function,
	&rmnet_smd_function,
	&rmnet_sdio_function,
	&rmnet_smd_sdio_function,
	&rmnet_function,
	&diag_function,
	&qdss_function,
	&serial_function,
	&adb_function,
	&ccid_function,
	&acm_function,
	&mtp_function,
	&ptp_function,
#ifdef CONFIG_USB_ANDROID_CDC_ECM
	&ecm_function,
#else
	&rndis_function,
	&rndis_qc_function,
#endif
	&mass_storage_function,
	&accessory_function,
	&audio_source_function,
	&uasp_function,
	&hid_function,
	NULL
};
