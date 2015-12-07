#ifdef USE_TLS
if (unlikely(c->type==PROTO_TLS || c->type==PROTO_WSS)) {
						t_buf = buf;
						t_len = len;
						do {
							t_send_flags = send_flags;
							n = tls_encode(c, &t_buf, &t_len,
											&rest_buf, &rest_len,
											&t_send_flags);
							if (unlikely((n < 0) || (t_len &&
									 (_wbufq_add(c, t_buf, t_len) < 0)))) {
								lock_release(&c->write_lock);
								n=-1;
								response[1] = CONN_ERROR;
								c->state=S_CONN_BAD;
								c->timeout=get_ticks_raw(); /* force timeout */
								goto error;
							}
							t_buf = rest_buf;
							t_len = rest_len;
						} while(unlikely(rest_len && n > 0));
					} else
#endif /* USE_TLS */
						if (unlikely(len && (_wbufq_add(c, buf, len)<0))){
							lock_release(&c->write_lock);
							n=-1;
							response[1] = CONN_ERROR;
							c->state=S_CONN_BAD;
							c->timeout=get_ticks_raw(); /* force timeout */
							goto error;
						}
