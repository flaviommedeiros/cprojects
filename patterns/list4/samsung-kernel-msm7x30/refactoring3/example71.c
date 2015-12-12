switch (port_type) {
#ifdef CONFIG_SERIAL_8250
	case PORT_8250 ... PORT_MAX_8250:
		ret = serial8250_register_port(&port);
		break;
#endif
#ifdef CONFIG_SERIAL_OF_PLATFORM_NWPSERIAL
	case PORT_NWPSERIAL:
		ret = nwpserial_register_port(&port);
		break;
#endif
	default:
		/* need to add code for these */
	case PORT_UNKNOWN:
		dev_info(&ofdev->dev, "Unknown serial port found, ignored\n");
		ret = -ENODEV;
		break;
	}
