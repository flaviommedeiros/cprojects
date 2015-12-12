switch (iforce->bus) {
#ifdef CONFIG_JOYSTICK_IFORCE_USB
	case IFORCE_USB:
		usb_kill_urb(iforce->irq);
		usb_kill_urb(iforce->out);
		usb_kill_urb(iforce->ctrl);
		break;
#endif
#ifdef CONFIG_JOYSTICK_IFORCE_232
	case IFORCE_232:
		//TODO: Wait for the last packets to be sent
		break;
#endif
	}
