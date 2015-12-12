uint8_t usb_descriptor_string_product[] = {
#ifdef HACKRF_ONE
	22,						// bLength
	USB_DESCRIPTOR_TYPE_STRING,		// bDescriptorType
	'H', 0x00,
	'a', 0x00,
	'c', 0x00,
	'k', 0x00,
	'R', 0x00,
	'F', 0x00,
	' ', 0x00,
	'O', 0x00,
	'n', 0x00,
	'e', 0x00,
#elif JAWBREAKER
	36,						// bLength
	USB_DESCRIPTOR_TYPE_STRING,		// bDescriptorType
	'H', 0x00,
	'a', 0x00,
	'c', 0x00,
	'k', 0x00,
	'R', 0x00,
	'F', 0x00,
	' ', 0x00,
	'J', 0x00,
	'a', 0x00,
	'w', 0x00,
	'b', 0x00,
	'r', 0x00,
	'e', 0x00,
	'a', 0x00,
	'k', 0x00,
	'e', 0x00,
	'r', 0x00,
#else
	14,						// bLength
	USB_DESCRIPTOR_TYPE_STRING,		// bDescriptorType
	'H', 0x00,
	'a', 0x00,
	'c', 0x00,
	'k', 0x00,
	'R', 0x00,
	'F', 0x00,
#endif
};
