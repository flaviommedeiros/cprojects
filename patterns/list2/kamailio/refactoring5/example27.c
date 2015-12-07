#ifdef USE_TLS
if (unlikely(c->type==PROTO_TLS || c->type==PROTO_WSS)) {
			/* for TLS the TLS processing and the send must happen
			   atomically w/ respect to other sends on the same connection
			   (otherwise reordering might occur which would break TLS) =>
			   lock.
			*/
			response[1] = CONN_NOP;
			t_buf = buf;
			t_len = len;
			lock_get(&c->write_lock);
				do {
					t_send_flags = send_flags;
					n = tls_encode(c, &t_buf, &t_len, &rest_buf, &rest_len,
									&t_send_flags);
					if (likely(n > 0)) {
						n = tcpconn_do_send(fd, c, t_buf, t_len, t_send_flags,
												&resp, 1);
						if (likely(response[1] != CONN_QUEUED_WRITE ||
									resp == CONN_ERROR))
							/* don't overwrite a previous CONN_QUEUED_WRITE
							   unless error */
							response[1] = resp;
					} else if (unlikely(n < 0)) {
						response[1] = CONN_ERROR;
						break;
					}
					/* else do nothing for n (t_len) == 0, keep
					   the last reponse */
					t_buf = rest_buf;
					t_len = rest_len;
				} while(unlikely(rest_len && n > 0));
			lock_release(&c->write_lock);
		} else
#endif
			n = tcpconn_do_send(fd, c, buf, len, send_flags, &response[1], 0);
