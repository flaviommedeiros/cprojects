#ifdef USE_TLS
if (type==PROTO_TLS){
		if (tls_tcpconn_init(c, sock)==-1) goto error;
	}else
#endif /* USE_TLS*/
	{
		c->type=PROTO_TCP;
		c->rcv.proto=PROTO_TCP;
		c->timeout=get_ticks_raw()+cfg_get(tcp, tcp_cfg, con_lifetime);
		c->lifetime = cfg_get(tcp, tcp_cfg, con_lifetime);
	}
