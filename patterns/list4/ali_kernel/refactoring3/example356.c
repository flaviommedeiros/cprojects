switch (iforce->bus) {
#ifdef CONFIG_JOYSTICK_IFORCE_USB
		case IFORCE_USB:
			usb_kill_urb(iforce->irq);

			/* The device was unplugged before the file
			 * was released */
			if (iforce->usbdev == NULL) {
				iforce_delete_device(iforce);
				kfree(iforce);
			}
		break;
#endif
	}
