#ifdef USE_SCTP
if (sctp_disable)
#endif
		for(r=PROTO_NONE; r<=PROTO_LAST; r++){
			if (nxt_proto[r]==PROTO_SCTP)
				nxt_proto[r]=nxt_proto[PROTO_SCTP];
		}
