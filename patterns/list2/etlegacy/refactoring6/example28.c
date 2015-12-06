if (to.type != NA_BROADCAST && to.type != NA_IP
#ifdef FEATURE_IPV6
	    && to.type != NA_IP6 && to.type != NA_MULTICAST6
#endif
	    )
	{
		Com_Error(ERR_FATAL, "Sys_SendPacket: bad address type");
		return;
	}
