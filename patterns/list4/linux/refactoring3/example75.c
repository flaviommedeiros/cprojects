switch (port_type) {
#ifdef CONFIG_SERIAL_8250
	case PORT_8250 ... PORT_MAX_8250:
	{
		struct uart_8250_port port8250;
		memset(&port8250, 0, sizeof(port8250));
		port8250.port = port;

		if (port.fifosize)
			port8250.capabilities = UART_CAP_FIFO;

		if (of_property_read_bool(ofdev->dev.of_node,
					  "auto-flow-control"))
			port8250.capabilities |= UART_CAP_AFE;

		ret = serial8250_register_8250_port(&port8250);
		break;
	}
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
