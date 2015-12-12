switch (iforce->bus) {
#ifdef CONFIG_JOYSTICK_IFORCE_USB
	case IFORCE_USB:
		input_dev->id.bustype = BUS_USB;
		input_dev->dev.parent = &iforce->usbdev->dev;
		break;
#endif
#ifdef CONFIG_JOYSTICK_IFORCE_232
	case IFORCE_232:
		input_dev->id.bustype = BUS_RS232;
		input_dev->dev.parent = &iforce->serio->dev;
		break;
#endif
	}
