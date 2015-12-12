switch (musb_mode) {
#ifdef	CONFIG_USB_MUSB_HDRC_HCD
	case MUSB_HOST:		/* Force VBUS valid, ID = 0 */
		devconf2 |= CONF2_FORCE_HOST;
		break;
#endif
#ifdef	CONFIG_USB_GADGET_MUSB_HDRC
	case MUSB_PERIPHERAL:	/* Force VBUS valid, ID = 1 */
		devconf2 |= CONF2_FORCE_DEVICE;
		break;
#endif
#ifdef	CONFIG_USB_MUSB_OTG
	case MUSB_OTG:		/* Don't override the VBUS/ID comparators */
		devconf2 |= CONF2_NO_OVERRIDE;
		break;
#endif
	default:
		pr_info(KERN_INFO "Unsupported mode %u\n", musb_mode);
	}
