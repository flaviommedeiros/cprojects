switch (p->iotype) {
	case UPIO_MEM:
	case UPIO_MEM32:
#ifdef CONFIG_SERIAL_8250_AU1X00
	case UPIO_AU:
#endif
	case UPIO_DWAPB:
		p->serial_out(p, offset, value);
		p->serial_in(p, UART_LCR);	/* safe, no side-effects */
		break;
	default:
		p->serial_out(p, offset, value);
	}
