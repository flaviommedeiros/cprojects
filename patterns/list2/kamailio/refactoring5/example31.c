#ifdef TCP_ASYNC
if (unlikely(tcpconn->flags & F_CONN_WRITE_W))
				n=io_watch_chg(&io_h, tcpconn->s, POLLIN| POLLOUT, -1);
			else
#endif /* TCP_ASYNC */
				n=io_watch_add(&io_h, tcpconn->s, POLLIN, F_TCPCONN, tcpconn);
