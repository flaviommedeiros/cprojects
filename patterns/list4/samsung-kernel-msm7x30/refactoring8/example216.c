static const struct usb_device_id device_table[] = {
	{USB_DEVICE(0x102c, 0x6151), .driver_info = SENSOR_PAS106},
#if !defined CONFIG_USB_ET61X251 && !defined CONFIG_USB_ET61X251_MODULE
	{USB_DEVICE(0x102c, 0x6251), .driver_info = SENSOR_TAS5130CXX},
#endif
	{}
};
