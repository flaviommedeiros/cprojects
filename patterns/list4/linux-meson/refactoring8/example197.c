static const struct usb_device_id	products [] = {
/*
 * BLACKLIST !!
 *
 * First blacklist any products that are egregiously nonconformant
 * with the CDC Ethernet specs.  Minor braindamage we cope with; when
 * they're not even trying, needing a separate driver is only the first
 * of the differences to show up.
 */

#define	ZAURUS_MASTER_INTERFACE \
	.bInterfaceClass	= USB_CLASS_COMM, \
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET, \
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE

/* SA-1100 based Sharp Zaurus ("collie"), or compatible;
 * wire-incompatible with true CDC Ethernet implementations.
 * (And, it seems, needlessly so...)
 */
{
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor		= 0x04DD,
	.idProduct		= 0x8004,
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
},

/* PXA-25x based Sharp Zaurii.  Note that it seems some of these
 * (later models especially) may have shipped only with firmware
 * advertising false "CDC MDLM" compatibility ... but we're not
 * clear which models did that, so for now let's assume the worst.
 */
{
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor		= 0x04DD,
	.idProduct		= 0x8005,	/* A-300 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
}, {
	.match_flags	=   USB_DEVICE_ID_MATCH_INT_INFO
			  | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor		= 0x04DD,
	.idProduct		= 0x8006,	/* B-500/SL-5600 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
}, {
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
	          | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor		= 0x04DD,
	.idProduct		= 0x8007,	/* C-700 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
}, {
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor               = 0x04DD,
	.idProduct              = 0x9031,	/* C-750 C-760 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
}, {
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor               = 0x04DD,
	.idProduct              = 0x9032,	/* SL-6000 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
}, {
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor               = 0x04DD,
	/* reported with some C860 units */
	.idProduct              = 0x9050,	/* C-860 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
},

/* Olympus has some models with a Zaurus-compatible option.
 * R-1000 uses a FreeScale i.MXL cpu (ARMv4T)
 */
{
	.match_flags    =   USB_DEVICE_ID_MATCH_INT_INFO
		 | USB_DEVICE_ID_MATCH_DEVICE,
	.idVendor               = 0x07B4,
	.idProduct              = 0x0F02,	/* R-1000 */
	ZAURUS_MASTER_INTERFACE,
	.driver_info		= 0,
},

/* LG Electronics VL600 wants additional headers on every frame */
{
	USB_DEVICE_AND_INTERFACE_INFO(0x1004, 0x61aa, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},

/* Logitech Harmony 900 - uses the pseudo-MDLM (BLAN) driver */
{
	USB_DEVICE_AND_INTERFACE_INFO(0x046d, 0xc11f, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_MDLM, USB_CDC_PROTO_NONE),
	.driver_info		= 0,
},

/* Novatel USB551L and MC551 - handled by qmi_wwan */
{
	USB_DEVICE_AND_INTERFACE_INFO(NOVATEL_VENDOR_ID, 0xB001, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},

/* Novatel E362 - handled by qmi_wwan */
{
	USB_DEVICE_AND_INTERFACE_INFO(NOVATEL_VENDOR_ID, 0x9010, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},

/* Dell Wireless 5800 (Novatel E362) - handled by qmi_wwan */
{
	USB_DEVICE_AND_INTERFACE_INFO(DELL_VENDOR_ID, 0x8195, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},

/* Dell Wireless 5800 (Novatel E362) - handled by qmi_wwan */
{
	USB_DEVICE_AND_INTERFACE_INFO(DELL_VENDOR_ID, 0x8196, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},

/* Dell Wireless 5804 (Novatel E371) - handled by qmi_wwan */
{
	USB_DEVICE_AND_INTERFACE_INFO(DELL_VENDOR_ID, 0x819b, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},

/* AnyDATA ADU960S - handled by qmi_wwan */
{
	USB_DEVICE_AND_INTERFACE_INFO(0x16d5, 0x650a, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},

/* Huawei E1820 - handled by qmi_wwan */
{
	USB_DEVICE_INTERFACE_NUMBER(HUAWEI_VENDOR_ID, 0x14ac, 1),
	.driver_info = 0,
},

/* Realtek RTL8152 Based USB 2.0 Ethernet Adapters */
#if defined(CONFIG_USB_RTL8152) || defined(CONFIG_USB_RTL8152_MODULE)
{
	USB_DEVICE_AND_INTERFACE_INFO(REALTEK_VENDOR_ID, 0x8152, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = 0,
},
#endif

/*
 * WHITELIST!!!
 *
 * CDC Ether uses two interfaces, not necessarily consecutive.
 * We match the main interface, ignoring the optional device
 * class so we could handle devices that aren't exclusively
 * CDC ether.
 *
 * NOTE:  this match must come AFTER entries blacklisting devices
 * because of bugs/quirks in a given product (like Zaurus, above).
 */
{
	/* ZTE (Vodafone) K3805-Z */
	.match_flags    =   USB_DEVICE_ID_MATCH_VENDOR
		 | USB_DEVICE_ID_MATCH_PRODUCT
		 | USB_DEVICE_ID_MATCH_INT_INFO,
	.idVendor               = ZTE_VENDOR_ID,
	.idProduct		= 0x1003,
	.bInterfaceClass	= USB_CLASS_COMM,
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET,
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE,
	.driver_info = (unsigned long)&wwan_info,
}, {
	/* ZTE (Vodafone) K3806-Z */
	.match_flags    =   USB_DEVICE_ID_MATCH_VENDOR
		 | USB_DEVICE_ID_MATCH_PRODUCT
		 | USB_DEVICE_ID_MATCH_INT_INFO,
	.idVendor               = ZTE_VENDOR_ID,
	.idProduct		= 0x1015,
	.bInterfaceClass	= USB_CLASS_COMM,
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET,
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE,
	.driver_info = (unsigned long)&wwan_info,
}, {
	/* ZTE (Vodafone) K4510-Z */
	.match_flags    =   USB_DEVICE_ID_MATCH_VENDOR
		 | USB_DEVICE_ID_MATCH_PRODUCT
		 | USB_DEVICE_ID_MATCH_INT_INFO,
	.idVendor               = ZTE_VENDOR_ID,
	.idProduct		= 0x1173,
	.bInterfaceClass	= USB_CLASS_COMM,
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET,
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE,
	.driver_info = (unsigned long)&wwan_info,
}, {
	/* ZTE (Vodafone) K3770-Z */
	.match_flags    =   USB_DEVICE_ID_MATCH_VENDOR
		 | USB_DEVICE_ID_MATCH_PRODUCT
		 | USB_DEVICE_ID_MATCH_INT_INFO,
	.idVendor               = ZTE_VENDOR_ID,
	.idProduct		= 0x1177,
	.bInterfaceClass	= USB_CLASS_COMM,
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET,
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE,
	.driver_info = (unsigned long)&wwan_info,
}, {
	/* ZTE (Vodafone) K3772-Z */
	.match_flags    =   USB_DEVICE_ID_MATCH_VENDOR
		 | USB_DEVICE_ID_MATCH_PRODUCT
		 | USB_DEVICE_ID_MATCH_INT_INFO,
	.idVendor               = ZTE_VENDOR_ID,
	.idProduct		= 0x1181,
	.bInterfaceClass	= USB_CLASS_COMM,
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET,
	.bInterfaceProtocol	= USB_CDC_PROTO_NONE,
	.driver_info = (unsigned long)&wwan_info,
}, {
	/* Telit modules */
	USB_VENDOR_AND_INTERFACE_INFO(0x1bc7, USB_CLASS_COMM,
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE),
	.driver_info = (kernel_ulong_t) &wwan_info,
}, {
	USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_ETHERNET,
			USB_CDC_PROTO_NONE),
	.driver_info = (unsigned long) &cdc_info,
}, {
	USB_INTERFACE_INFO(USB_CLASS_COMM, USB_CDC_SUBCLASS_MDLM,
			USB_CDC_PROTO_NONE),
	.driver_info = (unsigned long)&wwan_info,

}, {
	/* Various Huawei modems with a network port like the UMG1831 */
	.match_flags    =   USB_DEVICE_ID_MATCH_VENDOR
		 | USB_DEVICE_ID_MATCH_INT_INFO,
	.idVendor               = HUAWEI_VENDOR_ID,
	.bInterfaceClass	= USB_CLASS_COMM,
	.bInterfaceSubClass	= USB_CDC_SUBCLASS_ETHERNET,
	.bInterfaceProtocol	= 255,
	.driver_info = (unsigned long)&wwan_info,
},
	{ },		// END
};
