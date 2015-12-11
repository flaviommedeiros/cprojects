#ifdef NS_ENABLE_SSL
if(mosq->want_connect){
					rc = mosquitto__socket_connect_tls(mosq);
					if(rc) return rc;
				}else
#endif
				{
					rc = mosquitto_loop_read(mosq, max_packets);
					if(rc || mosq->sock == INVALID_SOCKET){
						return rc;
					}
				}
