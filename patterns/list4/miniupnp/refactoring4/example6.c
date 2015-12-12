#ifdef UPNP_STRICT
if(!ext_port || !protocol || !r_host)
#else
	if(!ext_port || !protocol)
#endif /* UPNP_STRICT */
	{
		ClearNameValueList(&data);
		SoapError(h, 402, "Invalid Args");
		return;
	}
