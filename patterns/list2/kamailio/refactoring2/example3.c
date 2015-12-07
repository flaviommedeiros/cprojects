#ifdef USE_TCP
if (tls_disable || tcp_disable)
#endif
#endif
		for(r=PROTO_NONE; r<=PROTO_LAST; r++){
			if (nxt_proto[r]==PROTO_TLS)
				nxt_proto[r]=nxt_proto[PROTO_TLS];
		}
