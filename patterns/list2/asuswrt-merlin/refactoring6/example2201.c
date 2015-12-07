if (!raw
#ifdef WHY_BOTHER_WE_CAN_ASSUME_IP_MATCHES
	 || G.local_addr->u.sa.sa_family != AF_INET
#endif
	) {
 bail:
		WRITE_ERR(FTP_BADCMD);
		return;
	}
