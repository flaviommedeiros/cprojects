#ifdef WITH_SOCKS
if(mosq->socks5_host){
		rc = _mosquitto_socket_connect(mosq, mosq->socks5_host, mosq->socks5_port, mosq->bind_address, blocking);
	}else
#endif
	{
		rc = _mosquitto_socket_connect(mosq, mosq->host, mosq->port, mosq->bind_address, blocking);
	}
