switch (retcode)
		{
		case -EBUSY:		/* Device or resource busy */
			upslog_with_errno(LOG_CRIT, "Got disconnected by another driver");
		case -EPERM:		/* Operation not permitted */
		case -ENODEV:		/* No such device */
		case -EACCES:		/* Permission denied */
		case -EIO:		/* I/O error */
		case -ENXIO:		/* No such device or address */
		case -ENOENT:		/* No such file or directory */
			/* Uh oh, got to reconnect! */
			hd = NULL;
			return FALSE;

		case 1:
			break;	/* Found! */

		case 0:
			continue;

		case -ETIMEDOUT:	/* Connection timed out */
		case -EOVERFLOW:	/* Value too large for defined data type */
#ifdef EPROTO
		case -EPROTO:		/* Protocol error */
#endif
		case -EPIPE:		/* Broken pipe */
		default:
			/* Don't know what happened, try again later... */
			continue;
		}
