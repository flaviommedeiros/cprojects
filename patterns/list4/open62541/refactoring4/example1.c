#ifdef _WIN32
if(last_error == WSAEINTR || last_error == WSAEWOULDBLOCK)
#else
		if(errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
#endif
            return UA_STATUSCODE_GOOD; /* retry */
        else {
            socket_close(connection);
            return UA_STATUSCODE_BADCONNECTIONCLOSED;
        }
