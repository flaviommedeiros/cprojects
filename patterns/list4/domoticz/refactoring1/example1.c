if((int)mosq->sock >= 0){
#ifdef WITH_BROKER
		HASH_DELETE(hh_sock, db->contexts_by_sock, mosq);
#endif
		rc = COMPAT_CLOSE(mosq->sock);
		mosq->sock = INVALID_SOCKET;
#ifdef WITH_WEBSOCKETS
	}else if(mosq->sock == WEBSOCKET_CLIENT){
		if(mosq->state != mosq_cs_disconnecting){
			mosq->state = mosq_cs_disconnect_ws;
		}
		if(mosq->wsi){
			libwebsocket_callback_on_writable(mosq->ws_context, mosq->wsi);
		}
		mosq->sock = INVALID_SOCKET;
#endif
	}
#endif
