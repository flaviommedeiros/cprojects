switch (fifo_mode) {
	case 0:
		OMAP_BULK_EP("ep1in",  USB_DIR_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_DIR_OUT | 2);
		OMAP_INT_EP("ep3in",   USB_DIR_IN  | 3, 16);
		break;
	case 1:
		OMAP_BULK_EP("ep1in",  USB_DIR_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_DIR_OUT | 2);
		OMAP_INT_EP("ep9in",   USB_DIR_IN  | 9, 16);

		OMAP_BULK_EP("ep3in",  USB_DIR_IN  | 3);
		OMAP_BULK_EP("ep4out", USB_DIR_OUT | 4);
		OMAP_INT_EP("ep10in",  USB_DIR_IN  | 10, 16);

		OMAP_BULK_EP("ep5in",  USB_DIR_IN  | 5);
		OMAP_BULK_EP("ep5out", USB_DIR_OUT | 5);
		OMAP_INT_EP("ep11in",  USB_DIR_IN  | 11, 16);

		OMAP_BULK_EP("ep6in",  USB_DIR_IN  | 6);
		OMAP_BULK_EP("ep6out", USB_DIR_OUT | 6);
		OMAP_INT_EP("ep12in",  USB_DIR_IN  | 12, 16);

		OMAP_BULK_EP("ep7in",  USB_DIR_IN  | 7);
		OMAP_BULK_EP("ep7out", USB_DIR_OUT | 7);
		OMAP_INT_EP("ep13in",  USB_DIR_IN  | 13, 16);
		OMAP_INT_EP("ep13out", USB_DIR_OUT | 13, 16);

		OMAP_BULK_EP("ep8in",  USB_DIR_IN  | 8);
		OMAP_BULK_EP("ep8out", USB_DIR_OUT | 8);
		OMAP_INT_EP("ep14in",  USB_DIR_IN  | 14, 16);
		OMAP_INT_EP("ep14out", USB_DIR_OUT | 14, 16);

		OMAP_BULK_EP("ep15in",  USB_DIR_IN  | 15);
		OMAP_BULK_EP("ep15out", USB_DIR_OUT | 15);

		break;

#ifdef	USE_ISO
	case 2:			/* mixed iso/bulk */
		OMAP_ISO_EP("ep1in",   USB_DIR_IN  | 1, 256);
		OMAP_ISO_EP("ep2out",  USB_DIR_OUT | 2, 256);
		OMAP_ISO_EP("ep3in",   USB_DIR_IN  | 3, 128);
		OMAP_ISO_EP("ep4out",  USB_DIR_OUT | 4, 128);

		OMAP_INT_EP("ep5in",   USB_DIR_IN  | 5, 16);

		OMAP_BULK_EP("ep6in",  USB_DIR_IN  | 6);
		OMAP_BULK_EP("ep7out", USB_DIR_OUT | 7);
		OMAP_INT_EP("ep8in",   USB_DIR_IN  | 8, 16);
		break;
	case 3:			/* mixed bulk/iso */
		OMAP_BULK_EP("ep1in",  USB_DIR_IN  | 1);
		OMAP_BULK_EP("ep2out", USB_DIR_OUT | 2);
		OMAP_INT_EP("ep3in",   USB_DIR_IN  | 3, 16);

		OMAP_BULK_EP("ep4in",  USB_DIR_IN  | 4);
		OMAP_BULK_EP("ep5out", USB_DIR_OUT | 5);
		OMAP_INT_EP("ep6in",   USB_DIR_IN  | 6, 16);

		OMAP_ISO_EP("ep7in",   USB_DIR_IN  | 7, 256);
		OMAP_ISO_EP("ep8out",  USB_DIR_OUT | 8, 256);
		OMAP_INT_EP("ep9in",   USB_DIR_IN  | 9, 16);
		break;
#endif

	/* add more modes as needed */

	default:
		ERR("unsupported fifo_mode #%d\n", fifo_mode);
		return -ENODEV;
	}
