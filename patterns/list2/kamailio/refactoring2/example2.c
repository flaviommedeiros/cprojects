#ifdef USE_TCP
if (tcp_disable)
#endif
		for(r=PROTO_NONE; r<=PROTO_LAST; r++){
			if (nxt_proto[r]==PROTO_TCP)
				nxt_proto[r]=nxt_proto[PROTO_TCP];
		}
