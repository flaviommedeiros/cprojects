#ifdef WITH_SOCKS
if(mosq->socks5_host){
			rc = mosquitto__socks5_read(mosq);
		}else
#endif
		{
			rc = _mosquitto_packet_read(mosq);
		}
