if ( ( nsent == -1 ) && 
#if defined(EAGAIN) && EAGAIN != EWOULDBLOCK
	    	      ( socket_errno( ) != EAGAIN ) &&
#endif
		        ( socket_errno( ) != EWOULDBLOCK ) ) {
		__xmlIOErr(XML_FROM_HTTP, 0, "send failed\n");
		if ( total_sent == 0 )
		    total_sent = -1;
		break;
	    }
	    else {
	        /*
		**  No data sent
		**  Since non-blocking sockets are used, wait for 
		**  socket to be writable or default timeout prior
		**  to retrying.
		*/

		struct timeval	tv;
		fd_set		wfd;

		tv.tv_sec = timeout;
		tv.tv_usec = 0;
		FD_ZERO( &wfd );
		FD_SET( ctxt->fd, &wfd );
		(void)select( ctxt->fd + 1, NULL, &wfd, NULL, &tv );
	    }
