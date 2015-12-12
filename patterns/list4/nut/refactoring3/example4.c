switch (ret)
	{
	case -EBUSY:		/* Device or resource busy */
		fatal_with_errno(EXIT_FAILURE, "Got disconnected by another driver");

	case -EPERM:		/* Operation not permitted */
		fatal_with_errno(EXIT_FAILURE, "Permissions problem");

	case -EPIPE:		/* Broken pipe */
		if (usb_clear_halt(udev, 0x81) == 0) {
			upsdebugx(1, "Stall condition cleared");
			break;
		}
#ifdef ETIME
	case -ETIME:		/* Timer expired */
#endif
		if (usb_reset(udev) == 0) {
			upsdebugx(1, "Device reset handled");
		}
	case -ENODEV:		/* No such device */
	case -EACCES:		/* Permission denied */
	case -EIO:		/* I/O error */
	case -ENXIO:		/* No such device or address */
	case -ENOENT:		/* No such file or directory */
		/* Uh oh, got to reconnect! */
		usb->close(udev);
		udev = NULL;
		break;

	case -ETIMEDOUT:	/* Connection timed out */
		upsdebugx (3, "riello_command err: Resource temporarily unavailable");


	case -EOVERFLOW:	/* Value too large for defined data type */
#ifdef EPROTO
	case -EPROTO:		/* Protocol error */
#endif
		break;
	default:
		break;
	}
