static struct pxa25x_udc memory = {
	.gadget = {
		.ops		= &pxa25x_udc_ops,
		.ep0		= &memory.ep[0].ep,
		.name		= driver_name,
		.dev = {
			.init_name	= "gadget",
			.release	= nop_release,
		},
	},

	/* control endpoint */
	.ep[0] = {
		.ep = {
			.name		= ep0name,
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= EP0_FIFO_SIZE,
		},
		.dev		= &memory,
		.reg_udccs	= &UDCCS0,
		.reg_uddr	= &UDDR0,
	},

	/* first group of endpoints */
	.ep[1] = {
		.ep = {
			.name		= "ep1in-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= BULK_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 1,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.reg_udccs	= &UDCCS1,
		.reg_uddr	= &UDDR1,
	},
	.ep[2] = {
		.ep = {
			.name		= "ep2out-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= BULK_FIFO_SIZE,
		.bEndpointAddress = 2,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.reg_udccs	= &UDCCS2,
		.reg_ubcr	= &UBCR2,
		.reg_uddr	= &UDDR2,
	},
#ifndef CONFIG_USB_PXA25X_SMALL
	.ep[3] = {
		.ep = {
			.name		= "ep3in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 3,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.reg_udccs	= &UDCCS3,
		.reg_uddr	= &UDDR3,
	},
	.ep[4] = {
		.ep = {
			.name		= "ep4out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddress = 4,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.reg_udccs	= &UDCCS4,
		.reg_ubcr	= &UBCR4,
		.reg_uddr	= &UDDR4,
	},
	.ep[5] = {
		.ep = {
			.name		= "ep5in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= INT_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 5,
		.bmAttributes	= USB_ENDPOINT_XFER_INT,
		.reg_udccs	= &UDCCS5,
		.reg_uddr	= &UDDR5,
	},

	/* second group of endpoints */
	.ep[6] = {
		.ep = {
			.name		= "ep6in-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= BULK_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 6,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.reg_udccs	= &UDCCS6,
		.reg_uddr	= &UDDR6,
	},
	.ep[7] = {
		.ep = {
			.name		= "ep7out-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= BULK_FIFO_SIZE,
		.bEndpointAddress = 7,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.reg_udccs	= &UDCCS7,
		.reg_ubcr	= &UBCR7,
		.reg_uddr	= &UDDR7,
	},
	.ep[8] = {
		.ep = {
			.name		= "ep8in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 8,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.reg_udccs	= &UDCCS8,
		.reg_uddr	= &UDDR8,
	},
	.ep[9] = {
		.ep = {
			.name		= "ep9out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddress = 9,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.reg_udccs	= &UDCCS9,
		.reg_ubcr	= &UBCR9,
		.reg_uddr	= &UDDR9,
	},
	.ep[10] = {
		.ep = {
			.name		= "ep10in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= INT_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 10,
		.bmAttributes	= USB_ENDPOINT_XFER_INT,
		.reg_udccs	= &UDCCS10,
		.reg_uddr	= &UDDR10,
	},

	/* third group of endpoints */
	.ep[11] = {
		.ep = {
			.name		= "ep11in-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= BULK_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 11,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.reg_udccs	= &UDCCS11,
		.reg_uddr	= &UDDR11,
	},
	.ep[12] = {
		.ep = {
			.name		= "ep12out-bulk",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= BULK_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= BULK_FIFO_SIZE,
		.bEndpointAddress = 12,
		.bmAttributes	= USB_ENDPOINT_XFER_BULK,
		.reg_udccs	= &UDCCS12,
		.reg_ubcr	= &UBCR12,
		.reg_uddr	= &UDDR12,
	},
	.ep[13] = {
		.ep = {
			.name		= "ep13in-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 13,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.reg_udccs	= &UDCCS13,
		.reg_uddr	= &UDDR13,
	},
	.ep[14] = {
		.ep = {
			.name		= "ep14out-iso",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= ISO_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= ISO_FIFO_SIZE,
		.bEndpointAddress = 14,
		.bmAttributes	= USB_ENDPOINT_XFER_ISOC,
		.reg_udccs	= &UDCCS14,
		.reg_ubcr	= &UBCR14,
		.reg_uddr	= &UDDR14,
	},
	.ep[15] = {
		.ep = {
			.name		= "ep15in-int",
			.ops		= &pxa25x_ep_ops,
			.maxpacket	= INT_FIFO_SIZE,
		},
		.dev		= &memory,
		.fifo_size	= INT_FIFO_SIZE,
		.bEndpointAddress = USB_DIR_IN | 15,
		.bmAttributes	= USB_ENDPOINT_XFER_INT,
		.reg_udccs	= &UDCCS15,
		.reg_uddr	= &UDDR15,
	},
#endif /* !CONFIG_USB_PXA25X_SMALL */
};
