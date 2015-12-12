switch (baud) {
		case SERIAL_BAUD_1200:    port_baud = B1200; break;
		case SERIAL_BAUD_1800:    port_baud = B1800; break;
		case SERIAL_BAUD_2400:    port_baud = B2400; break;
		case SERIAL_BAUD_4800:    port_baud = B4800; break;
		case SERIAL_BAUD_9600:    port_baud = B9600; break;
		case SERIAL_BAUD_19200:   port_baud = B19200; break;
		case SERIAL_BAUD_38400:   port_baud = B38400; break;
		case SERIAL_BAUD_57600:   port_baud = B57600; break;
		case SERIAL_BAUD_115200:  port_baud = B115200; break;
		case SERIAL_BAUD_230400:  port_baud = B230400; break;
#ifdef B460800
		case SERIAL_BAUD_460800:  port_baud = B460800; break;
#endif /* B460800 */
#ifdef B921600
		case SERIAL_BAUD_921600:  port_baud = B921600; break;
#endif /* B921600 */
#ifdef B500000
		case SERIAL_BAUD_500000:  port_baud = B500000; break;
#endif /* B500000 */
#ifdef B576000
		case SERIAL_BAUD_576000:  port_baud = B576000; break;
#endif /* B576000 */
#ifdef B1000000
		case SERIAL_BAUD_1000000: port_baud = B1000000; break;
#endif /* B1000000 */
#ifdef B1500000
		case SERIAL_BAUD_1500000: port_baud = B1500000; break;
#endif /* B1500000 */
#ifdef B2000000
		case SERIAL_BAUD_2000000: port_baud = B2000000; break;
#endif /* B2000000 */

		case SERIAL_BAUD_INVALID:
		default:
			return PORT_ERR_UNKNOWN;
	}
