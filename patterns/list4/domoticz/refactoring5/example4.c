#ifdef WITH_SOCKS
if(mosq->socks5_host){
		return mosquitto__socks5_send(mosq);
	}else
#endif
	{
		return _mosquitto_send_connect(mosq, mosq->keepalive, mosq->clean_session);
	}
