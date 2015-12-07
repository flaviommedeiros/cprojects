if (dst.proto == PROTO_WS)
	{
		if (unlikely(tcp_disable))
		{
			STATS_TX_DROPS;
			LM_WARN("TCP disabled\n");
			pkg_free(send_buf);
			tcpconn_put(con);
			return -1;
		}		
	}
#ifdef USE_TLS
	else if (dst.proto == PROTO_WSS)
	{
		if (unlikely(tls_disable))
		{
			STATS_TX_DROPS;
			LM_WARN("TLS disabled\n");
			pkg_free(send_buf);
			tcpconn_put(con);
			return -1;
		}		
	}
#endif
