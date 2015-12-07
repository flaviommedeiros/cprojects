#ifdef USE_TLS
if (unlikely(type==PROTO_TLS))
		*res_si=find_si(&ip, 0, PROTO_TLS);
	else
#endif
		*res_si=find_si(&ip, 0, PROTO_TCP);
