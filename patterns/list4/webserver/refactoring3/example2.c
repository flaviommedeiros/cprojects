switch (error) {
		case EAGAIN:
			TRACE (ENTRIES",write", "write len=%d (written=0), EAGAIN\n", buf_len);
			return ret_eagain;
#ifdef ENOTCONN
		case ENOTCONN:
#endif
		case EPIPE:
		case ECONNRESET:
			TRACE (ENTRIES",write", "write len=%d (written=0), EOF\n", buf_len);
			return ret_eof;
		default:
			LOG_ERRNO_S (error, cherokee_err_error,
			             CHEROKEE_ERROR_SSL_SW_DEFAULT);
		}
