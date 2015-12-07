if ( msg->rcv.proto==PROTO_TCP
#ifdef USE_TLS
					|| msg->rcv.proto==PROTO_TLS
#endif
			   ){

				if (a->val[0].type==NOSUBTYPE)	port=msg->via1->port;
				else if (a->val[0].type==NUMBER_ST) port=(int)a->val[0].u.number;
				else{
					LM_CRIT("bad force_tcp_alias"
							" port type %d\n", a->val[0].type);
					ret=E_BUG;
					goto error;
				}

				if (tcpconn_add_alias(msg->rcv.proto_reserved1, port,
									msg->rcv.proto)!=0){
					LM_ERR("receive_msg: tcp alias failed\n");
					ret=E_UNSPEC;
					goto error;
				}
			}
