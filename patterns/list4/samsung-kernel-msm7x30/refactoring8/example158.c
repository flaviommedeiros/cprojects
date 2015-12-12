static struct usb_device_id stub_table[] = {
#if 0
	/* just an example */
	{ USB_DEVICE(0x05ac, 0x0301) },   /* Mac 1 button mouse */
	{ USB_DEVICE(0x0430, 0x0009) },   /* Plat Home Keyboard */
	{ USB_DEVICE(0x059b, 0x0001) },   /* Iomega USB Zip 100 */
	{ USB_DEVICE(0x04b3, 0x4427) },   /* IBM USB CD-ROM */
	{ USB_DEVICE(0x05a9, 0xa511) },   /* LifeView USB cam */
	{ USB_DEVICE(0x55aa, 0x0201) },   /* Imation card reader */
	{ USB_DEVICE(0x046d, 0x0870) },   /* Qcam Express(QV-30) */
	{ USB_DEVICE(0x04bb, 0x0101) },   /* IO-DATA HD 120GB */
	{ USB_DEVICE(0x04bb, 0x0904) },   /* IO-DATA USB-ET/TX */
	{ USB_DEVICE(0x04bb, 0x0201) },   /* IO-DATA USB-ET/TX */
	{ USB_DEVICE(0x08bb, 0x2702) },   /* ONKYO USB Speaker */
	{ USB_DEVICE(0x046d, 0x08b2) },   /* Logicool Qcam 4000 Pro */
#endif
	/* magic for wild card */
	{ .driver_info = 1 },
	{ 0, }                                     /* Terminating entry */
};
