static const struct usb_device_id af9035_id_table[] = {
	/* AF9035 devices */
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_9035,
		&af9035_props, "Afatech AF9035 reference design", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1000,
		&af9035_props, "Afatech AF9035 reference design", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1001,
		&af9035_props, "Afatech AF9035 reference design", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1002,
		&af9035_props, "Afatech AF9035 reference design", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AFATECH, USB_PID_AFATECH_AF9035_1003,
		&af9035_props, "Afatech AF9035 reference design", NULL) },
	{ DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_T_STICK,
		&af9035_props, "TerraTec Cinergy T Stick", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A835,
		&af9035_props, "AVerMedia AVerTV Volar HD/PRO (A835)", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_B835,
		&af9035_props, "AVerMedia AVerTV Volar HD/PRO (A835)", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_1867,
		&af9035_props, "AVerMedia HD Volar (A867)", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_A867,
		&af9035_props, "AVerMedia HD Volar (A867)", NULL) },
	{ DVB_USB_DEVICE(USB_VID_AVERMEDIA, USB_PID_AVERMEDIA_TWINSTAR,
		&af9035_props, "AVerMedia Twinstar (A825)", NULL) },
	{ DVB_USB_DEVICE(USB_VID_ASUS, USB_PID_ASUS_U3100MINI_PLUS,
		&af9035_props, "Asus U3100Mini Plus", NULL) },
        { DVB_USB_DEVICE(USB_VID_TERRATEC, 0x00aa,
		&af9035_props, "TerraTec Cinergy T Stick (rev. 2)", NULL) },
	/* IT9135 devices */
#if 0
	{ DVB_USB_DEVICE(0x048d, 0x9135,
		&af9035_props, "IT9135 reference design", NULL) },
	{ DVB_USB_DEVICE(0x048d, 0x9006,
		&af9035_props, "IT9135 reference design", NULL) },
#endif
	/* XXX: that same ID [0ccd:0099] is used by af9015 driver too */
	{ DVB_USB_DEVICE(USB_VID_TERRATEC, 0x0099,
		&af9035_props, "TerraTec Cinergy T Stick Dual RC (rev. 2)", NULL) },
	{ DVB_USB_DEVICE(USB_VID_LEADTEK, 0x6a05,
		&af9035_props, "Leadtek WinFast DTV Dongle Dual", NULL) },
	{ DVB_USB_DEVICE(USB_VID_HAUPPAUGE, 0xf900,
		&af9035_props, "Hauppauge WinTV-MiniStick 2", NULL) },
	{ }
};
