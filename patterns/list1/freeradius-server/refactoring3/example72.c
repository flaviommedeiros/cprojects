switch (default_log.dst) {

#ifdef HAVE_SYSLOG_H
	case L_DST_SYSLOG:
		switch (type) {
		case L_DBG:
		case L_DBG_WARN:
		case L_DBG_ERR:
		case L_DBG_ERR_REQ:
		case L_DBG_WARN_REQ:
			type = LOG_DEBUG;
			break;

		case L_AUTH:
		case L_PROXY:
		case L_ACCT:
			type = LOG_NOTICE;
			break;

		case L_INFO:
			type = LOG_INFO;
			break;

		case L_WARN:
			type = LOG_WARNING;
			break;

		case L_ERR:
			type = LOG_ERR;
			break;
		}
		syslog(type, "%s", buffer);
		break;
#endif

	case L_DST_FILES:
	case L_DST_STDOUT:
	case L_DST_STDERR:
		return write(default_log.fd, buffer, strlen(buffer));

	default:
	case L_DST_NULL:	/* should have been caught above */
		break;
	}
