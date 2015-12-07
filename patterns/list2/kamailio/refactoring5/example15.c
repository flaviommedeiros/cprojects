#ifdef USE_TLS
if (u->type==SIPS_URI_T)
		proto = PROTO_TLS;
	else
#endif
		proto = u->proto;
