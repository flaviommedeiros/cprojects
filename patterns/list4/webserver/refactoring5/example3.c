#ifdef HAVE_IPV6
if ((family == AF_INET6) &&
		    (errno == EAFNOSUPPORT))
		{
			LOG_WARNING (CHEROKEE_ERROR_SOCKET_NO_IPV6);
		} else
#endif
		{
			LOG_ERRNO (errno, cherokee_err_error, CHEROKEE_ERROR_SOCKET_NEW_SOCKET);
			return ret_error;
		}
