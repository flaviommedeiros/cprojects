#ifdef READ_WS
if (unlikely(con->type == PROTO_WS || con->type == PROTO_WSS))
				bytes=tcp_read_ws(con, read_flags);
			else
#endif
				bytes=tcp_read_headers(con, read_flags);
