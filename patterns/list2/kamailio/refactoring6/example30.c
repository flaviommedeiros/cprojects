if (msg->via1->alias && cfg_get(tcp, tcp_cfg, accept_aliases) && 
				(((rcv_info->proto==PROTO_TCP) && !tcp_disable)
#ifdef USE_TLS
					|| ((rcv_info->proto==PROTO_TLS) && !tls_disable)
#endif
				)
			){
			if (tcpconn_add_alias(rcv_info->proto_reserved1, msg->via1->port,
									rcv_info->proto)!=0){
				LM_ERR("tcp alias failed\n");
				/* continue */
			}
		}
