switch (p->iotype) {
	case UPIO_HUB6:
		p->serial_in = hub6_serial_in;
		p->serial_out = hub6_serial_out;
		break;

	case UPIO_MEM:
		p->serial_in = mem_serial_in;
		p->serial_out = mem_serial_out;
		break;

	case UPIO_RM9000:
	case UPIO_MEM32:
		p->serial_in = mem32_serial_in;
		p->serial_out = mem32_serial_out;
		break;

#ifdef CONFIG_SERIAL_8250_AU1X00
	case UPIO_AU:
		p->serial_in = au_serial_in;
		p->serial_out = au_serial_out;
		break;
#endif
	case UPIO_TSI:
		p->serial_in = tsi_serial_in;
		p->serial_out = tsi_serial_out;
		break;

	case UPIO_DWAPB:
		p->serial_in = mem_serial_in;
		p->serial_out = dwapb_serial_out;
		break;

	default:
		p->serial_in = io_serial_in;
		p->serial_out = io_serial_out;
		break;
	}
