#ifdef USE_SSL
if (port->ssl)
				ereport(LOG,
						(errmsg("replication connection authorized: user=%s SSL enabled (protocol=%s, cipher=%s, compression=%s)",
								port->user_name, SSL_get_version(port->ssl), SSL_get_cipher(port->ssl),
								SSL_get_current_compression(port->ssl) ? _("on") : _("off"))));
			else
#endif
				ereport(LOG,
						(errmsg("replication connection authorized: user=%s",
								port->user_name)));
