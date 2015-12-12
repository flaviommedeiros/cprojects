switch (iforce->bus) {
#ifdef CONFIG_JOYSTICK_IFORCE_USB
	case IFORCE_USB:
		iforce_usb_delete(iforce);
		break;
#endif
#ifdef CONFIG_JOYSTICK_IFORCE_232
	case IFORCE_232:
		//TODO: Wait for the last packets to be sent
		break;
#endif
	}
