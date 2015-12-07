#ifdef USE_TLS
if (unlikely(c->type==PROTO_TLS))
			bytes=tls_read(c, read_flags);
		else
#endif
			bytes=tcp_read(c, read_flags);
