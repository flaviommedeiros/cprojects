if (!is_local(Trans) && ((Trans->uas.request->rcv.proto==PROTO_TCP)
#ifdef USE_TLS
				|| (Trans->uas.request->rcv.proto==PROTO_TLS)
#endif /* USE_TLS */
		)){
		if ((via_id.s=id_builder(Trans->uas.request,
									(unsigned int*)&via_id.len))==0){
			LOG(L_ERR, "ERROR: build_local: id builder failed\n");
			/* try to continue without id */
		}
	}
