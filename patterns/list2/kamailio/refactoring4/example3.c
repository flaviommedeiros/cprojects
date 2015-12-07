#ifdef USE_DNS_FAILOVER
if ((uri2dst(NULL,&dst, msg,  uri, proto)==0) || (dst.send_sock==0))
#else
        if ((uri2dst(&dst, msg,  uri, proto)==0) || (dst.send_sock==0))
#endif 
        {
		LOG(L_ERR, "forward_sl_request: no socket found\n");
		return -1;
	}
