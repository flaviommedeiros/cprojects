switch (err) {
#if defined(EWOULDBLOCK) && (EWOULDBLOCK != EAGAIN)
		case EWOULDBLOCK:
#endif
		case EAGAIN:
			return ret_eagain;

		case EPIPE:
		case ECONNRESET:
#ifdef ENOTCONN
		case ENOTCONN:
#endif
			socket->status = socket_closed;
		case ETIMEDOUT:
		case EHOSTUNREACH:
			return ret_error;
		}
