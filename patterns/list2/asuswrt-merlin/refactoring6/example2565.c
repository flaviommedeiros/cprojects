if(proto != IPPROTO_UDP && proto != IPPROTO_TCP
#ifdef IPPROTO_UDPITE
	   && atoi(protocol) != IPPROTO_UDPLITE
#endif
	  )
	{
		SoapError(h, 705, "ProtocolNotSupported");
		goto clear_and_exit;
	}
