if (!conn->client.is_ssl
#ifndef NO_SSL
			    || sslize(conn, conn->ctx->ssl_ctx, SSL_accept)
#endif
			        ) {


				process_new_connection(conn);
			}
