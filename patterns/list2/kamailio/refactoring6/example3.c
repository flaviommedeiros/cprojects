if (msg && (
#ifdef USE_TCP
		(msg->rcv.proto==PROTO_TCP)
#ifdef USE_TLS
			|| (msg->rcv.proto==PROTO_TLS)
#endif
#ifdef USE_SCTP
			||
#endif /* USE_SCTP */
#endif /* USE_TCP */
#ifdef USE_SCTP
			(msg->rcv.proto==PROTO_SCTP)
#endif /* USE_SCTP */
			)){
		if  ((id_buf=id_builder(msg, &id_len))==0){
			LM_ERR("id_builder failed\n");
			return 0; /* we don't need to free anything,
			                 nothing alloc'ed yet*/
		}
		LM_DBG("id added: <%.*s>, rcv proto=%d\n",
				(int)id_len, id_buf, msg->rcv.proto);
		extra_params.s=id_buf;
		extra_params.len=id_len;
	}
