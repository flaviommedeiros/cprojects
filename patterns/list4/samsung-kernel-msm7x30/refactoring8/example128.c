struct usb_string		fsg_strings[] = {
#ifndef FSG_NO_DEVICE_STRINGS
	{FSG_STRING_MANUFACTURER,	fsg_string_manufacturer},
	{FSG_STRING_PRODUCT,		fsg_string_product},
	{FSG_STRING_SERIAL,		""},
	{FSG_STRING_CONFIG,		fsg_string_config},
#endif
	{FSG_STRING_INTERFACE,		fsg_string_interface},
	{}
};
