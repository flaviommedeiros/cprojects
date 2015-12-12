switch(ret)
	{
	case -EBUSY:	/* Device or resource busy */
	case -EPERM:	/* Operation not permitted */
	case -ENODEV:	/* No such device */
	case -EACCES:	/* Permission denied */
	case -EIO:	/* I/O error */
	case -ENXIO:	/* No such device or address */
	case -ENOENT:	/* No such file or directory */
	case -EPIPE:	/* Broken pipe */
	case -ENOSYS:	/* Function not implemented */
		upslogx(LOG_DEBUG, "%s: %s", desc, usb_strerror());
		return ret;

	case -ETIMEDOUT:	/* Connection timed out */
		upsdebugx(2, "%s: Connection timed out", desc);
		return 0;

	case -EOVERFLOW:	/* Value too large for defined data type */
#ifdef EPROTO
	case -EPROTO:	/* Protocol error */
#endif
		upsdebugx(2, "%s: %s", desc, usb_strerror());
		return 0;

	default:	/* Undetermined, log only */
		upslogx(LOG_DEBUG, "%s: %s", desc, usb_strerror());
		return 0;
	}
