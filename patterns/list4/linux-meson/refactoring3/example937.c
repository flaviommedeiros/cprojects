switch (iforce->bus) {

#ifdef CONFIG_JOYSTICK_IFORCE_232
		case IFORCE_232:
		if (empty)
			iforce_serial_xmit(iforce);
		break;
#endif
#ifdef CONFIG_JOYSTICK_IFORCE_USB
		case IFORCE_USB:

		if (iforce->usbdev && empty &&
			!test_and_set_bit(IFORCE_XMIT_RUNNING, iforce->xmit_flags)) {

			iforce_usb_xmit(iforce);
		}
		break;
#endif
	}
