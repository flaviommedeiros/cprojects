if (
#ifdef USE_TCP
			dst.proto==PROTO_TCP
			|| dst.proto==PROTO_WS
#ifdef USE_TLS
			|| dst.proto==PROTO_TLS
			|| dst.proto==PROTO_WSS
#endif
#ifdef USE_SCTP
			||
#endif /* USE_SCTP */
#endif /* USE_TCP */
#ifdef USE_SCTP
			dst.proto==PROTO_SCTP
#endif /* USE_SCTP */
			){
		/* find id in i param if it exists */
		if (msg->via1->i && msg->via1->i->value.s){
			s=msg->via1->i->value.s;
			len=msg->via1->i->value.len;
			LM_DBG("i=%.*s\n",len, ZSW(s));
			if (reverse_hex2int(s, len, (unsigned int*)&dst.id)<0){
				LM_ERR("bad via i param \"%.*s\"\n", len, ZSW(s));
				dst.id=0;
			}
		}		
				
	}
