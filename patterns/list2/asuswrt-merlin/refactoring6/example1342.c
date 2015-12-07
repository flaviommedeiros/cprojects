if ((peeraddr_in->sin_family != PF_INET)
#ifdef HAVE_IPV6
	    && (peeraddr_in->sin_family != PF_INET6)
#endif
	    ) {
		DEBUG(0,("cm_prepare_connection: got unexpected family %d\n",
			peeraddr_in->sin_family));
		result = NT_STATUS_UNSUCCESSFUL;
		goto done;
	}
