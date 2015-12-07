#ifdef USE_TLS
if (unlikely(c->type==PROTO_TLS)) {
			/* for TLS the TLS processing and the send must happen
			   atomically w/ respect to other sends on the same connection
			   (otherwise reordering might occur which would break TLS) =>
			   lock. However in this case this send will always be the first.
			   We can have the send() outside the lock only if this is the
			   first and only send (tls_encode is not called again), or
			   this is the last send for a tls_encode() loop and all the
			   previous ones did return CONN_NEW_COMPLETE or CONN_EOF.
			*/
				response[1] = CONN_NOP;
				t_buf = buf;
				t_len = len;
				lock_get(&c->write_lock);
redo_tls_encode:
					t_send_flags = dst->send_flags;
					n = tls_encode(c, &t_buf, &t_len, &rest_buf, &rest_len,
									&t_send_flags);
					/* There are 4 cases:
					   1. entire buffer consumed from the first try
					     (rest_len == rest_buf == 0)
					   2. rest_buf & first call
					   3. rest_buf & not first call
						  3a. CONN_NEW_COMPLETE or CONN_EOF
						  3b. CONN_NEW_PENDING_WRITE
					   4. entire buffer consumed, but not first call
					       4a. CONN_NEW_COMPLETE or CONN_EOF
						   4b. CONN_NEW_PENDING_WRITE
						We misuse response[1] == CONN_NOP to test for the
						first call.
					*/
					if (unlikely(n < 0)) {
						lock_release(&c->write_lock);
						goto conn_wait_error;
					}
					if (likely(rest_len == 0)) {
						/* 1 or 4*: CONN_NEW_COMPLETE, CONN_EOF,  CONN_NOP
						    or CONN_NEW_PENDING_WRITE (*rest_len == 0) */
						if (likely(response[1] != CONN_NEW_PENDING_WRITE)) {
							/* 1 or 4a => it's safe to do the send outside the
							   lock (it will either send directly or
							   wbufq_insert())
							*/
							lock_release(&c->write_lock);
							if (likely(t_len != 0)) {
								n=tcpconn_1st_send(fd, c, t_buf, t_len,
													t_send_flags,
													&response[1], 0);
							} else { /* t_len == 0 */
								if (response[1] == CONN_NOP) {
									/* nothing to send (e.g  parallel send
									   tls_encode queues some data and then
									   WANT_READ => this tls_encode will queue
									   the cleartext too and will have nothing
									   to send right now) and initial send =>
									   behave as if the send was successful
									   (but never return EOF here) */
									response[1] = CONN_NEW_COMPLETE;
								}
							}
							/* exit */
						} else {
							/* CONN_NEW_PENDING_WRITE:  4b: it was a
							   repeated tls_encode() (or otherwise we would
							   have here CONN_NOP) => add to the queue */
							if (unlikely(t_len &&
											_wbufq_add(c, t_buf, t_len) < 0)) {
								response[1] = CONN_ERROR;
								n = -1;
							}
							lock_release(&c->write_lock);
							/* exit (no send) */
						}
					} else {  /* rest_len != 0 */
						/* 2 or 3*: if tls_encode hasn't finished, we have to
						   call tcpconn_1st_send() under lock (otherwise if it
						   returns CONN_NEW_PENDING_WRITE, there is no way
						   to find the right place to add the new queued
						   data from the 2nd tls_encode()) */
						if (likely((response[1] == CONN_NOP /*2*/ ||
									response[1] == CONN_NEW_COMPLETE /*3a*/ ||
									response[1] == CONN_EOF /*3a*/) && t_len))
							n = tcpconn_1st_send(fd, c, t_buf, t_len,
													t_send_flags,
													&response[1], 1);
						else if (unlikely(t_len &&
											_wbufq_add(c, t_buf, t_len) < 0)) {
							/*3b: CONN_NEW_PENDING_WRITE*/
							response[1] = CONN_ERROR;
							n = -1;
						}
						if (likely(n >= 0)) {
							/* if t_len == 0 => nothing was sent => previous
							   response will be kept */
							t_buf = rest_buf;
							t_len = rest_len;
							goto redo_tls_encode;
						} else {
							lock_release(&c->write_lock);
							/* error exit */
						}
					}
			} else
#endif /* USE_TLS */
				n=tcpconn_1st_send(fd, c, buf, len, dst->send_flags,
									&response[1], 0);
