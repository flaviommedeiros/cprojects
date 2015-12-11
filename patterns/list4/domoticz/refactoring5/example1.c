#ifdef NS_ENABLE_SSL
if(mosq->tls_cafile || mosq->tls_capath || mosq->tls_psk){
		hints.ai_family = PF_INET;
	}else
#endif
	{
		hints.ai_family = PF_UNSPEC;
	}
