if ((peeraddr_len != sizeof(struct sockaddr_in))
#ifdef HAVE_IPV6
	    && (peeraddr_len != sizeof(struct sockaddr_in6))
#endif
	    ) {
		DEBUG(0,("cm_prepare_connection: got unexpected peeraddr len %d\n",
			peeraddr_len));
		result = NT_STATUS_UNSUCCESSFUL;
		goto done;
	}
