switch (iforce->bus) {
#ifdef CONFIG_JOYSTICK_IFORCE_USB
		case IFORCE_USB:
			iforce->irq->dev = iforce->usbdev;
			if (usb_submit_urb(iforce->irq, GFP_KERNEL))
				return -EIO;
			break;
#endif
	}
