#ifdef OPENSSL_SYS_WINDOWS
if ( data->_errno == WSAETIMEDOUT)
#else
		if ( data->_errno == EAGAIN)
#endif
			{
			ret = 1;
			data->_errno = 0;
			}
		else
			ret = 0;
